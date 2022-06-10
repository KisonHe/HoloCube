#include "style.h"

lv_style_t default_style;

void load_common_style(){
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_black());
    lv_style_set_text_color(&default_style,lv_color_white());
}
