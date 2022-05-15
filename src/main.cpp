#include <Arduino.h>
#include "gui/gui.h"
void setup()
{
    Serial.begin(115200);
    guiSetUp();
    pinMode(22, OUTPUT);
}

void loop()
{
    
    log_w("Set to High");
    digitalWrite(22,HIGH);
    vTaskDelay(3000);
    log_w("Set to Low");
    digitalWrite(22,LOW);
    vTaskDelay(3000);
}
