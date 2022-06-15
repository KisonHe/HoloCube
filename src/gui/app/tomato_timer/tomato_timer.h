#pragma once
#include "../app.h"

struct tomato_timer_config
{
    // int32_t workingTime = 1500;//seconds
    int32_t workingTime = 5;//seconds
    int32_t shortBreakTime = 300;//seconds
    int32_t longBreakTime = 600;//seconds
};


class tomato_timer : public app_t
{
private:
    /* data */
    esp_err_t load_config(tomato_timer_config* config);
    esp_err_t save_config(tomato_timer_config* config);
    tomato_timer_config* cfg = nullptr;
    TickType_t StartClockTick = 0;
    uint32_t lastTimeSec = 0;
    lv_obj_t* min_label = nullptr;
    lv_obj_t* mid_label = nullptr;
    lv_obj_t* sec_label = nullptr;
    char min_str[3] = "00";
    char sec_str[3] = "00";
public:
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void deinit(TickType_t tick);
    void init_app_info(lv_obj_t* img);
    tomato_timer(/* args */);
    ~tomato_timer();
};
