/**
 * @file mainmenu_app.cpp
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mainmenu_app.h"
#include "esp32-hal-log.h"
#include "../stringtable.h"

mainmenu_app_t mainmenu_app;

mainmenu_app_t* mainmenu_app_t::mainmenu_app_ptr = nullptr;
lv_obj_t * label = nullptr;
mainmenu_app_t::mainmenu_app_t(/* args */):app_t(true){  
    if (mainmenu_app_ptr!=nullptr){
        log_e("FATAL: Multi instance of mainmenu_app");
        abort();
    }
    mainmenu_app_ptr = this;
}

mainmenu_app_t::~mainmenu_app_t(){
    mainmenu_app_ptr = nullptr;
}

mainmenu_app_t* mainmenu_app_t::get_mainmenu_app_ptr(){
    return mainmenu_app_ptr;
}

TickType_t mainmenu_app_t::init(TickType_t tick, intent_t& intent, lv_obj_t* screen){
    log_d("mainmenu_app_t::init with tick%d,screen%x",tick,screen);
    static lv_style_t default_style;
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_black());
    lv_style_set_text_color(&default_style,lv_color_white());


    strings::kh_load_all_font();

    label = lv_label_create(screen);
    if (label == nullptr) log_e("Fail to create label");
    lv_obj_add_style(label,&default_style,LV_STATE_DEFAULT);
    lv_obj_add_style(screen,&default_style,LV_STATE_DEFAULT);
    
    strings::kh_fonttool_set_lang(strings::English);
    lv_label_set_text(label,strings::kh_fonttool_get_text(strings::Language));
    log_w("%s",strings::kh_fonttool_get_text(strings::Language));
    lv_obj_center(label);
    const lv_font_t* tmp = nullptr;
    tmp = strings::kh_fonttool_get_font(strings::Language);
    if (tmp == nullptr){
        ESP_LOGE(TAG,"Fail to load font");
    }else{
        lv_obj_set_style_text_font(label,tmp,0);
    }
    return 1;
    
}
TickType_t mainmenu_app_t::handle(TickType_t tick){
    strings::kh_fonttool_set_lang(strings::Chinese);
    lv_label_set_text(label,strings::kh_fonttool_get_text(strings::Language));
    // log_w("%s",strings::kh_fonttool_get_text(strings::Language));
    lv_obj_center(label);
    const lv_font_t* tmp = nullptr;
    tmp = strings::kh_fonttool_get_font(strings::Language);
    if (tmp == nullptr){
        ESP_LOGE(TAG,"Fail to load font");
    }else{
        lv_obj_set_style_text_font(label,tmp,0);
    }
    return 1;
}
void mainmenu_app_t::deinit(TickType_t tick){

}