/**
 * @file mainmenu_app.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "app.h"

// Menu app should be Singleton
// https://stackoverflow.com/questions/27338175/how-to-create-class-with-only-one-instance-in-c
// class mainmenu_app_t : public app_t
// {
// private:
//     mainmenu_app_t(/* args */);
// public:
//     // uint8_t createMainMenuApp
//     static mainmenu_app_t * const mainmenu_app_ptr;
//     ~mainmenu_app_t();
// };

class mainmenu_app_t : public app_t
{
private:
    int index = 0;
    static mainmenu_app_t* mainmenu_app_ptr;
    static lv_obj_t* now_app_container;
    bool index_changed = false;
public:
    void notify_indev(int dir);
    static lv_obj_t* create_app_ctr(lv_obj_t* parent, app_info_t* app_info);
    static mainmenu_app_t* get_mainmenu_app_ptr();
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void init_app_info();
    void show_no_app();
    void deinit(TickType_t tick);
    mainmenu_app_t(/* args */);
    ~mainmenu_app_t();
};