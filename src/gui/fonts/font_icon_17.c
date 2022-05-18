/*******************************************************************************
 * Size: 17 px
 * Bpp: 4
 * Opts: --font /home/kisonhe/Downloads/MaterialIcons-Regular.ttf --symbols  --lcd --size 17 --bpp 4 --lv-include lvgl.h --format lvgl -o src/gui/fonts/font_icon_17.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_ICON_17
#define FONT_ICON_17 1
#endif

#if FONT_ICON_17

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E5D4 "" */
    0x0, 0xf0, 0x8c, 0x1, 0xfc, 0x93, 0xbd, 0xd6,
    0xca, 0x0, 0x71, 0x62, 0x10, 0x4, 0x49, 0x84,
    0x1, 0x8a, 0x65, 0xc, 0xad, 0x1d, 0x24, 0x1,
    0xc2, 0x8f, 0x35, 0x2e, 0x62, 0x1, 0xe2, 0x6a,
    0xdd, 0xa9, 0x88, 0x3, 0x8e, 0xad, 0x48, 0xa5,
    0xba, 0x30, 0xc, 0x75, 0x6a, 0x45, 0x2d, 0xd1,
    0x80, 0x71, 0x35, 0x6e, 0xd4, 0xc4, 0x1, 0xe1,
    0x37, 0x9a, 0x97, 0x31, 0x0, 0xe2, 0x9e, 0x86,
    0x56, 0x8e, 0x92, 0x0, 0xc5, 0x88, 0x40, 0x11,
    0x26, 0x10, 0x7, 0x24, 0xef, 0x75, 0xb2, 0x80,
    0x10
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 272, .box_w = 15, .box_h = 13, .ofs_x = 6, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58836, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 1,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t font_icon_17 = {
#else
lv_font_t font_icon_17 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = -2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_HOR,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_ICON_17*/

