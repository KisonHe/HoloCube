#pragma once
#include "freertos/FreeRTOS.h"
class app
{
private:
    /* data */
public:
    TickType_t init(TickType_t tick);
    TickType_t handle(TickType_t tick);
    TickType_t deinit(TickType_t tick);
    app(/* args */);
    ~app();
};


