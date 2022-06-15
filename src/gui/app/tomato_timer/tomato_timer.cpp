#include "tomato_timer.h"
#include <Arduino.h>
#include "gui/style/style.h"
// #include <FastLED.h>
char tomato_app_name[] = "Tomato Timer";
LV_IMG_DECLARE(tomato);
static app_info_t tomato_app_info = {
.name = tomato_app_name,
.logo = tomato
};

tomato_timer::tomato_timer(/* args */):app_t(true,nullptr,&tomato_app_info)
{
}

tomato_timer::~tomato_timer()
{
}
LV_FONT_DECLARE(font_ui_36);
TickType_t tomato_timer::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    cfg = new tomato_timer_config();
    load_config(cfg);
    app_screen = screen;
    log_w("init of tomato app!");
    mid_label = lv_label_create(app_screen);
    assert(mid_label!=nullptr);
    // lv_obj_add_style(text_lable, &default_style, 0); // todo selector
    lv_label_set_text(mid_label, ":"); // todo set font also,maybe need to change the struct
    lv_obj_set_style_text_font(mid_label,&lv_font_montserrat_48,0);
    lv_obj_align(mid_label, LV_ALIGN_CENTER, 0, 0);

    min_label = lv_label_create(app_screen);
    assert(min_label!=nullptr);
    // lv_obj_add_style(text_lable, &default_style, 0); // todo selector
    lv_label_set_text(min_label, min_str); // todo set font also,maybe need to change the struct
    lv_obj_set_style_text_font(min_label,&lv_font_montserrat_48,0);
    lv_obj_align_to(min_label,mid_label, LV_ALIGN_OUT_LEFT_MID, 0, 0);

    sec_label = lv_label_create(app_screen);
    assert(sec_label!=nullptr);
    // lv_obj_add_style(text_lable, &default_style, 0); // todo selector
    lv_label_set_text(sec_label, sec_str); // todo set font also,maybe need to change the struct
    lv_obj_set_style_text_font(sec_label,&lv_font_montserrat_48,0);
    lv_obj_align_to(sec_label,mid_label, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    // For debug
    StartClockTick = xTaskGetTickCount();
    return 1;
}
TickType_t tomato_timer::handle(TickType_t tick){
    // for debug only
    TickType_t nowTick = xTaskGetTickCount();
    if ((nowTick-StartClockTick)>pdMS_TO_TICKS(cfg->workingTime*1000 + 800))
        return 1; //time out
    uint32_t timeSec = cfg->workingTime - (nowTick - StartClockTick)/1000;
    if (timeSec==lastTimeSec)
        return 1;
    lastTimeSec = timeSec;
    uint8_t minute = timeSec/60;
    uint8_t seconds = timeSec%60;
    snprintf(min_str, sizeof(min_str), "%02d", minute);
    snprintf(sec_str, sizeof(sec_str), "%02d", seconds);
    lv_label_set_text(min_label, min_str);
    lv_label_set_text(sec_label, sec_str);
    return 1;
}
void tomato_timer::deinit(TickType_t tick){
    save_config(cfg);
    delete cfg;
}

void tomato_timer::init_app_info(lv_obj_t* img){
    // todo set name according to lang also
    // lv_img_set_src(helloworld_app_logo, &google);
    // lv_img_set_src(img, "S:/spiffs/google.bin");
}


esp_err_t tomato_timer::load_config(tomato_timer_config* config){
    //todo load the config somewhere
}

esp_err_t tomato_timer::save_config(tomato_timer_config* config){
    //todo save the config somewhere
    //todo only save if modified so should also read one
}

// tomato
tomato_timer main_tomato_timer;