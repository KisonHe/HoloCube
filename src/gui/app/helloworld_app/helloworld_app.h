#pragma once
#include "../app.h"

class helloworld_app : public app_t
{
private:
    /* data */
public:
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void deinit(TickType_t tick);
    void init_app_info();
    helloworld_app(/* args */);
    ~helloworld_app();
};

extern helloworld_app main_helloworld_app;
