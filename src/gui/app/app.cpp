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

std::vector<app_t*> app_t::app_list;

app_info_t* app_t::get_app_info_ptr(){
    return app_info_ptr;
}

app_t::app_t(bool if_push_2_list, app_config_t* app_config_ptr, app_info_t* app_info_ptr):app_config_ptr(app_config_ptr), app_info_ptr(app_info_ptr)
{
    //push self to app list
    if (if_push_2_list){
        app_list.push_back(this);
    }
    
}

app_t::~app_t()
{
    // what will happen if this is not in the app_list?
    app_list.erase(std::remove(app_list.begin(), app_list.end(), this), app_list.end()); 
    //check if self is in app list. if in then delete
}

