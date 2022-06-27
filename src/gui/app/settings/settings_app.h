#pragma once
#include "../app.h"

class settings_app : public app_t
{
private:
    /* data */
    lv_obj_t* text_lable = nullptr;
    int16_t cnt = 0;
public:
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void deinit(TickType_t tick);
    void init_app_info(lv_obj_t* img);
    settings_app(app_info_t* app_info);
    ~settings_app();
};

// extern helloworld_app main_helloworld_app;
