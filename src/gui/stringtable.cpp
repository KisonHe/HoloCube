/**
 * Generated File, Do not modify
 * 
 */
#include "stringtable.h"
#include <stdint.h>
#include "esp32-hal-log.h"

LV_FONT_DECLARE(font_ui);
const fonttype* font_ui_ptr = &font_ui;
LV_FONT_DECLARE(font_ui_25);
const fonttype* font_ui_25_ptr = &font_ui_25;
LV_FONT_DECLARE(font_icon);
const fonttype* font_icon_ptr = &font_icon;
LV_FONT_DECLARE(font_icon_17);
const fonttype* font_icon_17_ptr = &font_icon_17;
namespace strings
{
    Language_t CurrentLanguage = English; //When generating, set default to first lang

    static kh_textdata_t MainData[EndOfLanguages][EndOfTexts] = {

        { 
            {"Language", font_ui_ptr},
            {"", font_icon_ptr},
            {"", font_icon_17_ptr},
            {"Firmware: %s", font_ui_ptr},
            {"English", font_ui_25_ptr},
        },
        { 
            {"语言", font_ui_25_ptr},
            {"", font_icon_ptr},
            {"", font_icon_17_ptr},
            {"固件版本 %s", font_ui_ptr},
            {"简体中文", font_ui_25_ptr},
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

    const fonttype * kh_fonttool_get_font(ID id){
        if (id >= EndOfTexts)
            return nullptr;
        return (MainData[CurrentLanguage][id].fontptr);
    }

    int kh_fonttool_set_lang(Language_t lang){
        if (lang >= EndOfLanguages)
            return -1;
        CurrentLanguage = lang; 
        return 0; 
    }

    void kh_load_all_font(){
        return; // for lvgl format fonts are already loaded
    }
  
}