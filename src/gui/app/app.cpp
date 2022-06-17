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
std::vector<app_t*>* app_t::app_list_ptr = nullptr;

app_info_t* app_t::get_app_info_ptr(){
    return app_info_ptr;
}

app_t::app_t(bool if_push_2_list, app_config_t* app_config_ptr, app_info_t* app_info_ptr):app_config_ptr(app_config_ptr), app_info_ptr(app_info_ptr)
{
    log_v("app_t constructor of %x",this);
    if (app_list_ptr == nullptr){
        app_list_ptr = new std::vector<app_t*>;
    }
    //push self to app list
    if (if_push_2_list){
        log_d("pushing %x to app_list %x",this,app_list_ptr);
        app_list_ptr->push_back(this);
        log_v("pushing done. Now app_list is %d long",app_list_ptr->size());
    }
    
}

app_t::~app_t()
{
    log_d("app_t destructor of %x",this);
    // what will happen if this is not in the app_list?
    app_list_ptr->erase(std::remove(app_list_ptr->begin(), app_list_ptr->end(), this), app_list_ptr->end()); 
    //check if self is in app list. if in then delete
}

