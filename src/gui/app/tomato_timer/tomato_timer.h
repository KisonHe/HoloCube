#pragma once
#include "../app.h"

struct tomato_timer_config
{
    // int32_t workingTime = 1500;//seconds
    int32_t workingTime = 5;//seconds
    int32_t shortBreakTime = 300;//seconds
    int32_t longBreakTime = 600;//seconds
};

enum tomato_timer_state_t{
    timer_state_reset,  // Reset, the state right into app & after pressing reset btn
    timer_state_ring,   // Ring, the state when & after the timer expires
    timer_state_paused, // The state when timer gets paused
    timer_state_running // The state when timer is counting
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
    void state_init(tomato_timer_state_t s);
    void state_deinit(tomato_timer_state_t s);
    void state_handle(tomato_timer_state_t s);
    char min_str[3] = "00";
    char sec_str[3] = "00";
    tomato_timer_state_t state = timer_state_reset;
public:
    TickType_t init(TickType_t tick, intent_t& intent, lv_obj_t* screen);
    TickType_t handle(TickType_t tick);
    void deinit(TickType_t tick);
    void init_app_info(lv_obj_t* img);
    tomato_timer(/* args */);
    ~tomato_timer();
};
