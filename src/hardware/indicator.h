#pragma once
#include <stdint.h>
#include "esp_err.h"
namespace indicator{
struct color_rgb_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

esp_err_t set_color(color_rgb_t);

}

