#include "gui.h"

#include <Arduino.h>
#include <esp_log.h>
#include <FreeRTOS.h>
#include <freertos/timers.h>

// #include <TFT_eSPI.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#include <lvgl.h>
#include "lvgl_fs.h"
#include "app/maganer.h"
#include "stringtable.h"
#include "style/style.h"

#include "app/helloworld_app/helloworld_app.h"

static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];
TaskHandle_t lvgl_Task_Handle;
SemaphoreHandle_t lvgl_lock;

class LGFX : public lgfx::LGFX_Device
{
lgfx::Panel_ST7789     _panel_instance;
lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス
// lgfx::Light_PWM     _light_instance;
// lgfx::Touch_XPT2046     _touch_instance;

public:
  LGFX(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。
      cfg.spi_host = VSPI_HOST;     // 使用するSPIを選択  (VSPI_HOST or HSPI_HOST)
      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;    // 受信時のSPIクロック
      cfg.spi_3wire  = false;        // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = 0;          // Set the DMA channel (1 or 2. 0=disable)   使用するDMAチャンネルを設定 (0=DMA不使用)
      cfg.pin_sclk = 18;            // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 5;            // SPIのMOSIピン番号を設定
      cfg.pin_miso = -1;            // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   = 23;            // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。
      cfg.pin_cs           =    -1;  // CSが接続されているピン番号   (-1 = disable)
      cfg.pin_rst          =    4;  // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)
      cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   240;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   240;  // 実際に表示可能な幅
      cfg.panel_height     =   240;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};

LGFX tft;

static const char* TAG = "GUI";
#if LV_USE_LOG != 0
#if LV_LOG_PRINTF == 0
// TODO: Port this to esplog
/* Serial debugging */
static void my_print(const char * buf)
{
    Serial.print(buf);
    Serial.flush();
}
#endif
#endif


/* Display flushing */
static void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    // tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.pushPixels( ( uint16_t * )&color_p->full, w * h, true );
    // tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    tft.endWrite();
    // tft.pushPixelsDMA(,);

    lv_disp_flush_ready( disp );
}

static void lvgl_task(TimerHandle_t xTimer)
{
    xSemaphoreTake(lvgl_lock,portMAX_DELAY);

    // static lv_style_t default_style;
    // ESP_LOGD(TAG,"Initing lvgl's fs");
    // lv_fs_init();
    // lv_style_init(&default_style);
    // lv_style_set_bg_color(&default_style, lv_color_black());
    // lv_style_set_text_color(&default_style,lv_color_white());
    load_common_style();
    strings::kh_load_all_font();
    strings::kh_fonttool_set_lang(strings::English);


    // strings::kh_load_all_font();
    ESP_LOGD(TAG,"Cleaning lv_scr_act()");
    lv_obj_del(lv_scr_act());
    ESP_LOGD(TAG,"Initing app_manager");
    app_manager::manager_init();
    ESP_LOGD(TAG,"Done");

    // lv_obj_t * label = lv_label_create(lv_scr_act());
    // lv_obj_add_style(label,&default_style,LV_STATE_DEFAULT);
    // lv_obj_add_style(lv_scr_act(),&default_style,LV_STATE_DEFAULT);
    
    // strings::kh_fonttool_set_lang(strings::Chinese);
    // lv_label_set_text(label,strings::kh_fonttool_get_text(strings::Language));
    // log_w("%s",strings::kh_fonttool_get_text(strings::Language));
    // lv_obj_center(label);
    // const lv_font_t* tmp = nullptr;
    // tmp = strings::kh_fonttool_get_font(strings::Language);
    // if (tmp == nullptr){
    // }else{
    //     lv_obj_set_style_text_font(label,tmp,0);
    // }
    xSemaphoreGive(lvgl_lock);
    while (1)
    {
        if (xSemaphoreTake(lvgl_lock,0) == pdTRUE){ //give up timer handle if didn't get the lock
            app_manager::manager_handle();
            lv_timer_handler(); /* let the GUI do its work */
            xSemaphoreGive(lvgl_lock);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    
}

/**
 * @brief set up all gui stuff:
 *        1. Set up tft_espi
 *        2. Setup lvgl, set lvgl fs callbacks
 *        3. Load Cutsom Font then common styles
 *        4. Call lv_layout_init to init all layouts
 *        5. Set a freertos timer to call lv_timer_handler (The default timer task dont have enough
 *           stack to call lv_timer_handler so it is commented out and called in main loop instead)
 * 
 */
void guiSetUp(){
    
    // Begin set tft_espi
    tft.begin();          /* TFT init */
    // tft.initDMA();
    // tft.setRotation( 4 ); /* Landscape orientation, flipped */
    tft.setRotation( 2 ); /* Landscape orientation, not flipped for ez debug */
    // Set tft_espi Done


    // Begin init lvgl
    lvgl_lock = xSemaphoreCreateMutex();
    lv_init();
#if LV_USE_LOG != 0
#if LV_LOG_PRINTF == 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif
#endif
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
    xSemaphoreGive(lvgl_lock);

    xTaskCreatePinnedToCore(lvgl_task,
                            "LVGL FreeRTOS Timer",
                            8192,
                            nullptr,
                            0,
                            &lvgl_Task_Handle,
                            1);

    // main_helloworld_app.handle(0); // avoid o3

}

