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

TickType_t mainmenu_app_t::init(TickType_t tick, intent_t&& intent, lv_obj_t* screen){
    
}
TickType_t mainmenu_app_t::handle(TickType_t tick){

}
void mainmenu_app_t::deinit(TickType_t tick){

}