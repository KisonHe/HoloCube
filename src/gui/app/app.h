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
#include <vector>
struct app_config_t
{
    
};

struct app_info_t
{
    // the name shown below your logo to user. should be short, length is not checked
    char* name; //might change, like a lang change so not const
    // logo shown to user, should be no more than 128x128
    const lv_img_dsc_t& logo;
};

struct intent_t;

class app_t
{
private:

// public:   
protected:
    /* data */
    // Note: Must set these
    static std::vector<app_t*>* app_list_ptr;
    app_config_t* app_config_ptr = nullptr;
    app_info_t* app_info_ptr = nullptr;;
    lv_obj_t* app_screen = nullptr;

public:
    // static std::vector<app_t*>* app_list_ptr;
    // 普通app在init或者handle调用switch app或者exit (exit其实就是switch app)，app会产生一个intent,这个部分使用
    // copy,因为deinit要等到这次handle/init推出才run,deinit结束才是下一个app的init,此时intent可能生命周期结束
    // 但是init的intent是manager给的，因此没问题
    /**
     * @brief 
     * 
     * @param tick 
     * @param intent 
     * @param screen 
     * @return TickType_t how many ticks later the handle has to be called
     */
    virtual TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen) = 0;
    virtual TickType_t handle(TickType_t tick) = 0;
    // 不要在deinit里面清除 app_screen，manager会清掉。
    virtual void deinit(TickType_t tick) = 0;
    /**
     * @brief 用于初始化app的图片与名字
     * 
     */
    virtual void init_app_info() = 0;
    app_info_t* get_app_info_ptr();
    app_t(bool if_push_2_list, app_config_t* app_config_ptr, app_info_t* app_info_ptr);
    ~app_t();
};


struct intent_t
{
    app_t* source_app;
    app_t* target_app;
    char* msg;  //Arduino json?
    //data,last_app,current_app etc. last_app在manager那里检查一下,确保是正确的
};
