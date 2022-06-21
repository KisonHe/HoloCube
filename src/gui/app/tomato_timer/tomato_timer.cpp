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
    log_i("init of tomato app!");
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
    state = timer_state_reset;
    state_init(state);
    return 1;
}
TickType_t tomato_timer::handle(TickType_t tick){
    state_handle(state);
    // update the screen:
    // for debug only
    // uint32_t timeSec = 0;
    // uint8_t minute = 0;
    // uint8_t seconds = 0;
    // bool blink = false;
    // bool updateStr = false;
    // switch (state)
    // {
    // case Reset:
    // {
    //     blink = true;
    //     break;
    // }
    // case Running:
    // {
    //     TickType_t nowTick = xTaskGetTickCount();
    //     if ((nowTick-StartClockTick)>pdMS_TO_TICKS(cfg->workingTime*1000 + 800)){
    //         state = Reset;
    //         snprintf(min_str, sizeof(min_str), "%02d", 0);
    //         snprintf(sec_str, sizeof(sec_str), "%02d", 0);
    //         updateStr = true;
    //         break; //time out
    //     }
    //     timeSec = cfg->workingTime - (nowTick - StartClockTick)/1000;
    //     if (timeSec==lastTimeSec)
    //         break;//秒钟没变
    //     updateStr = true;
    //     lastTimeSec = timeSec;
    //     minute = timeSec / 60;
    //     seconds = timeSec % 60;
    //     snprintf(min_str, sizeof(min_str), "%02d", minute);
    //     snprintf(sec_str, sizeof(sec_str), "%02d", seconds);
    //     break;
    // }
    
    // default:
    //     break;
    // }
    // if (blink){
    //     if ((xTaskGetTickCount()%1000)<500){
    //         lv_obj_add_flag(mid_label, LV_OBJ_FLAG_HIDDEN);
    //     }else{
    //         lv_obj_clear_flag(mid_label, LV_OBJ_FLAG_HIDDEN);
    //     }
    // }
    // if (updateStr){
    //     updateStr = false;
    //     lv_label_set_text(min_label, min_str);
    //     lv_label_set_text(sec_label, sec_str);
    // }
    // // screen handle finish
    
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

void tomato_timer::state_init(tomato_timer_state_t s){
    switch (s)
    {
    case timer_state_reset:
    {
        break;
    }
    case timer_state_paused:
    {
        break;
    }
    case timer_state_running:
    {
        break;
    }
        
    
    default:
        break;
    }
}
void tomato_timer::state_deinit(tomato_timer_state_t s){

}
void tomato_timer::state_handle(tomato_timer_state_t s){

}

// tomato
tomato_timer main_tomato_timer;