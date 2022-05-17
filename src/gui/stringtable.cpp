/**
 * Generated File, Do not modify
 * 
 */
#include "stringtable.h"
#include <stdint.h>
#include "esp32-hal-log.h"

fonttype* font_ui_ptr;
fonttype* font_ui_25_ptr;
fonttype* font_icon_ptr;
fonttype* font_icon_17_ptr;
namespace strings
{
    Language_t CurrentLanguage = English; //When generating, set default to first lang

    static kh_textdata_t MainData[EndOfLanguages][EndOfTexts] = {

        { 
            {"Language", &font_ui_ptr},
            {"", &font_icon_ptr},
            {"", &font_icon_17_ptr},
            {"Firmware: %s", &font_ui_ptr},
            {"English", &font_ui_25_ptr},
        },
        { 
            {"语言", &font_ui_25_ptr},
            {"", &font_icon_ptr},
            {"", &font_icon_17_ptr},
            {"固件版本 %s", &font_ui_ptr},
            {"简体中文", &font_ui_25_ptr},
        },
    };
    
    static const char* FontNames[] = {  //help to load font from file system 
        "font_ui",
        "font_ui_25",
        "font_icon",
        "font_icon_17",
    };

    const char * kh_fonttool_get_text(ID id){
        if (id >= EndOfTexts)
            return nullptr;
        return MainData[CurrentLanguage][id].text;
    }

    fonttype * kh_fonttool_get_font(ID id){
        if (id >= EndOfTexts)
            return nullptr;
        return *(MainData[CurrentLanguage][id].fontptr_ptr);
    }

    int kh_fonttool_set_lang(Language_t lang){
        if (lang >= EndOfLanguages)
            return -1;
        CurrentLanguage = lang; 
        return 0; 
    }

    void kh_load_all_font(){ 
        font_ui_ptr = lv_font_load("S:/spiffs/font_ui.bin");
        if (font_ui_ptr == nullptr){log_e("Fail to load %s","S:/spiffs/font_ui.bin");}
        font_ui_25_ptr = lv_font_load("S:/spiffs/font_ui_25.bin");
        if (font_ui_25_ptr == nullptr){log_e("Fail to load %s","S:/spiffs/font_ui_25.bin");}
        font_icon_ptr = lv_font_load("S:/spiffs/font_icon.bin");
        if (font_icon_ptr == nullptr){log_e("Fail to load %s","S:/spiffs/font_icon.bin");}
        font_icon_17_ptr = lv_font_load("S:/spiffs/font_icon_17.bin");
        if (font_icon_17_ptr == nullptr){log_e("Fail to load %s","S:/spiffs/font_icon_17.bin");}
    }
  
}