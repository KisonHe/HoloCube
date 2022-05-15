#pragma once
#include <lvgl.h>


/*2: Stored in SPIFFS as "/spiffs/customfont.bin"
 *1: Format LVGL https://github.com/lvgl/lv_font_conv#cli-params; Simply Name the font to custom_font
 *0: No CJK Font, will set cjk_font to LV_FONT_DEFAULT*/
// BTW, Tested though platformIO's Program Size Test, if use 2, custom size will not get into data section auto
// So no need to comment src/gui/custom_font.c out

// Example-------------------------------

// Use 1
// Calculating size .pio/build/pico32/firmware.elf
//    text    data     bss     dec     hex filename
// 1091210  368784   69504 1529498  17569a .pio/build/pico32/firmware.elf

// Use 2, But Comment Nothing
// Calculating size .pio/build/pico32/firmware.elf
//    text    data     bss     dec     hex filename
// 1094158  361128   69496 1524782  17442e .pio/build/pico32/firmware.elf

// Use 2, And Comment Whole src/gui/custom_font.c out
// Calculating size .pio/build/pico32/firmware.elf
//    text    data     bss     dec     hex filename
// 1094158  361128   69496 1524782  17442e .pio/build/pico32/firmware.elf
#define CUSTOM_FONT_TYPE 2
extern lv_style_t s_font_10_blk;
extern lv_style_t s_font_12_blk;
extern lv_style_t s_font_14_blk;
extern const lv_font_t* p_custom_font;