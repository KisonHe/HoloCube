#include <Arduino.h>
#include "gui/gui.h"
#include "SPIFFS.h"
void setup()
{
    Serial.begin(115200);
    pinMode(22, OUTPUT);
    if (!SPIFFS.begin()){
        log_e("SPIFFS Mount Failed");
    }else{
        log_w("SPIFFS Mounted");
        // File root = SPIFFS.open("/");
        // File file = root.openNextFile(); 
        // while(file){
        //     Serial.print("FILE: ");
        //     Serial.println(file.name());
        //     file = root.openNextFile();
        // }
    }
    guiSetUp();
}

void loop()
{
    // Serial.println(GIT_REV);
    // log_w("Set to High");
    digitalWrite(22,HIGH);
    vTaskDelay(5);
    // log_w("Set to Low");
    digitalWrite(22,LOW);
    vTaskDelay(5);
}
