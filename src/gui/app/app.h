/**
 * @file app.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "freertos/FreeRTOS.h"
#include "lvgl.h"
struct app_config_t
{
    
};

struct app_info_t
{
    // the name shown below your logo to user. should be short, length is not checked
    char* name = nullptr; //might change, like a lang change so not const
    // logo shown to user, should be no more than 128x128
    lv_obj_t * logo = nullptr;
};

struct intent_t
{
    
};


class app_t
{
private:
    /* data */
    app_config_t* app_config_ptr;
    app_info_t* app_info_ptr;
public:
    const char *name;   //must set in 
    virtual TickType_t init(TickType_t tick) = 0;
    virtual TickType_t handle(TickType_t tick) = 0;
    virtual TickType_t deinit(TickType_t tick) = 0;
    app_t(bool if_push_2_list);
    ~app_t();
};




