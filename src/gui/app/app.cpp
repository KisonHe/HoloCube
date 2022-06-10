/**
 * @file app.cpp
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "app.h"
#include <algorithm>
#include <Arduino.h>
std::vector<app_t*> app_t::app_list;

app_info_t* app_t::get_app_info_ptr(){
    return app_info_ptr;
}

app_t::app_t(bool if_push_2_list, app_config_t* app_config_ptr, app_info_t* app_info_ptr):app_config_ptr(app_config_ptr), app_info_ptr(app_info_ptr)
{
    log_w("app_t constructor of %x",this);
    //push self to app list
    if (if_push_2_list){
        log_w("pushing %x to app_list %x",this,&app_list);
        app_list.push_back(this);
        log_w("pushing done. Now app_list is %d long",app_list.size());
    }
    
}

app_t::~app_t()
{
    log_w("app_t destructor of %x",this);
    // what will happen if this is not in the app_list?
    app_list.erase(std::remove(app_list.begin(), app_list.end(), this), app_list.end()); 
    //check if self is in app list. if in then delete
}

