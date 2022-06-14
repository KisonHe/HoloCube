#pragma once
#include "../app.h"

class tomato_timer : public app_t
{
private:
    /* data */
public:
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void deinit(TickType_t tick);
    void init_app_info(lv_obj_t* img);
    tomato_timer(/* args */);
    ~tomato_timer();
};
