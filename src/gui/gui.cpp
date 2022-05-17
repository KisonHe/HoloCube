#include "gui.h"

#include <Arduino.h>
#include <esp_log.h>
#include <FreeRTOS.h>
#include <freertos/timers.h>

#include <TFT_eSPI.h>

#include <lvgl.h>
#include "lvgl_fs.h"
#include "mainTabView.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "stringtable.h"

// extern "C" void lv_log_register_print_cb(lv_log_print_g_cb_t print_cb);
extern nvs_handle nvs_main_handle;

// static vars
static const uint16_t screenWidth  = TFT_WIDTH;
static const uint16_t screenHeight = TFT_HEIGHT;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

lv_style_t s_font_10_blk;
lv_style_t s_font_12_blk;
lv_style_t s_font_14_blk;

// TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
// 草，TFT_eSPI/TFT_Drivers/ILI9341_Defines.h 里面，#define TFT_WIDTH  240 #define TFT_HEIGHT 320，也就是长宽是按照rotation = 0的情况区分的，所以。。lvgl给的
// example里面screenWidth  = 320; screenHeight = 240;不适用于我们买的这个，你看lvgl里面又弄了rotation=1。。。
// 如果这样初始化，会导致长短边scale互换（不是xy互换！）

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
TimerHandle_t lv_timer = nullptr;

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
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}


TaskHandle_t lvgl_Task_Handle;
// int32_t mark = 0;
static void lvgl_task(TimerHandle_t xTimer)
{
    lv_fs_init();
    strings::kh_load_all_font();

    lv_obj_t * label = lv_label_create(lv_scr_act());
    strings::kh_fonttool_set_lang(strings::Chinese);
    lv_label_set_text(label,strings::kh_fonttool_get_text(strings::Language));
    log_w("%s",strings::kh_fonttool_get_text(strings::Language));
    lv_obj_center(label);
    lv_font_t* tmp = nullptr;
    tmp = strings::kh_fonttool_get_font(strings::Language);
    if (tmp == nullptr){
    }else{
        lv_obj_set_style_text_font(label,tmp,0);
    }
    // static uint32_t lastwake = 0;
    while (1)
    {
        lv_timer_handler(); /* let the GUI do its work */
        vTaskDelay(pdMS_TO_TICKS(5));
    }
    
}

/**
 * @brief here we init default screen's layout
 * 
 */
static void lv_layout_init(){
    lv_main_tabview_init();
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
    tft.setRotation( 4 ); /* Landscape orientation, flipped */
    // Set tft_espi Done


    // Begin init lvgl
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

    xTaskCreatePinnedToCore(lvgl_task,
                            "LVGL FreeRTOS Timer",
                            8192,
                            nullptr,
                            0,
                            &lvgl_Task_Handle,
                            1);

}

