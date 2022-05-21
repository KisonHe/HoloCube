#include <Arduino.h>
#include "gpio.h"
namespace GPIO_ns{
void Write(gpio_def_t gpio_def,uint8_t mode) // https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
{
    pinMode(gpio_def.GPIO_Pin,OUTPUT);
    if (mode)
        digitalWrite(gpio_def.GPIO_Pin,HIGH);
    else
        digitalWrite(gpio_def.GPIO_Pin,LOW);
}

void SetLow(gpio_def_t gpio_def) {
    Write(gpio_def,LOW);
}

void SetHigh(gpio_def_t gpio_def) {
    Write(gpio_def,HIGH);
}

bool Read(gpio_def_t gpio_def) {
    pinMode(gpio_def.GPIO_Pin,INPUT);
    return ((bool)digitalRead(gpio_def.GPIO_Pin));
}
}