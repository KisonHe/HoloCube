#ifndef GPIO_H
#define GPIO_H

#include <cstdint>

//https://docs.microsoft.com/en-us/cpp/preprocessor/token-pasting-operator-hash-hash?view=msvc-170


/**
 * @brief   Structure for describing gpio
 */
typedef struct {
    uint8_t GPIO_Pin;   //GPIO pin num
} gpio_def_t;

namespace GPIO_ns
{
    void Write(gpio_def_t gpio_def,uint8_t mode);
    void SetLow(gpio_def_t gpio_def);
    void SetHigh(gpio_def_t gpio_def);
    bool Read(gpio_def_t gpio_def);
};

#endif //GPIO_H
