#pragma once
#include "freertos/FreeRTOS.h"
class app
{
private:
    /* data */
public:
    const char *name;   //must set in 
    virtual TickType_t init(TickType_t tick) = 0;
    virtual TickType_t handle(TickType_t tick) = 0;
    virtual TickType_t deinit(TickType_t tick) = 0;
    app(/* args */);
    ~app();
};

class intent
{
private:
    /* data */
public:
    intent(/* args */);
    ~intent();
};

