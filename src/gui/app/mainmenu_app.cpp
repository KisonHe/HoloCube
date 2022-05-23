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
static lv_style_t default_style;
mainmenu_app_t* mainmenu_app_t::mainmenu_app_ptr = nullptr;
mainmenu_app_t::mainmenu_app_t(/* args */):app_t(false){  
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
    ESP_LOGD(TAG,"app_list is %d long",app_t::app_list.size());
    app_screen = screen;

    if (app_t::app_list.size() < 1){
        //no apps
        show_no_app();
    }else{
        for (std::vector<app_t*>::iterator it = app_t::app_list.begin(); it != app_t::app_list.end(); it++){
            if (*it == this) //skip menu itself
                ; //todo change constructor to true to verify this
            // 使用Tabview吗？ 
            // tabview怎样确保运行中创建/删除的app也会去除对应的tabview？ lv_obj_clean 掉一个tabview,他会自动去掉吗？
        }
    }

    return 1;
    
}
TickType_t mainmenu_app_t::handle(TickType_t tick){
    // strings::kh_fonttool_set_lang(strings::Chinese);
    // lv_label_set_text(label,strings::kh_fonttool_get_text(strings::Language));
    // // log_w("%s",strings::kh_fonttool_get_text(strings::Language));
    // lv_obj_center(label);
    // const lv_font_t* tmp = nullptr;
    // tmp = strings::kh_fonttool_get_font(strings::Language);
    // if (tmp == nullptr){
    //     ESP_LOGE(TAG,"Fail to load font");
    // }else{
    //     lv_obj_set_style_text_font(label,tmp,0);
    // }
    return 1;
}
void mainmenu_app_t::deinit(TickType_t tick){

}

void mainmenu_app_t::show_no_app(){
    // log_d("mainmenu_app_t::init with tick%d,screen%x",tick,screen);

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_black());
    lv_style_set_text_color(&default_style,lv_color_white());

    lv_obj_t * label = lv_label_create(app_screen);
    if (label == nullptr) log_e("Fail to create label");
    lv_obj_add_style(label,&default_style,LV_STATE_DEFAULT);
    lv_obj_add_style(app_screen,&default_style,LV_STATE_DEFAULT);
    
    
    lv_label_set_text(label,strings::kh_fonttool_get_text(strings::NoApp));
    log_w("%s",strings::kh_fonttool_get_text(strings::NoApp));
    lv_obj_center(label);
    const lv_font_t* tmp = nullptr;
    tmp = strings::kh_fonttool_get_font(strings::NoApp);
    if (tmp == nullptr){
        ESP_LOGE(TAG,"Fail to load font");
    }else{
        lv_obj_set_style_text_font(label,tmp,0);
    }
}