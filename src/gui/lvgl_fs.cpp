// #include <lvgl.h>
// #include <Arduino.h>
// #include <stdio.h>
// #include "lvgl_fs.h"

// static lv_fs_drv_t drv;

// //Need to init SPIFFS First TODO:Check if SPIFFS Initted
// static void * open_cb(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
// {
//     (void) drv;
//     (void) mode;

//     FILE * fp = fopen(path, "rb"); // only reading is supported

//     return fp;
// }

// static lv_fs_res_t close_cb(lv_fs_drv_t * drv, void * file_p)
// {
//     (void) drv;

//     fclose((FILE *)file_p);
//     return LV_FS_RES_OK;
// }

// static lv_fs_res_t read_cb(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
// {
//     (void) drv;

//     *br = fread(buf, 1, btr, (FILE *)file_p);
//     return (*br <= 0) ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
// }

// static lv_fs_res_t seek_cb(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t w)
// {
//     (void) drv;

//     uint32_t w2;
//     switch(w) {
//     case LV_FS_SEEK_SET:
//         w2 = SEEK_SET;
//         break;
//     case LV_FS_SEEK_CUR:
//         w2 = SEEK_CUR;
//         break;
//     case LV_FS_SEEK_END:
//         w2 = SEEK_END;
//         break;
//     default:
//         w2 = SEEK_SET;
//     }

//     fseek ((FILE *)file_p, pos, w2);

//     return LV_FS_RES_OK;
// }

// static lv_fs_res_t tell_cb(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
// {
//     (void) drv;

//     *pos_p = ftell((FILE *)file_p);

//     return LV_FS_RES_OK;
// }


// void lv_fs_init(void)
// {
//     lv_fs_drv_init(&drv);                     /*Basic initialization*/

//     drv.letter = 'S';                         /*An uppercase letter to identify the drive*/
//     drv.open_cb = open_cb;                 /*Callback to open a file*/
//     drv.close_cb = close_cb;               /*Callback to close a file*/
//     drv.read_cb = read_cb;                 /*Callback to read a file*/
//     drv.seek_cb = seek_cb;                 /*Callback to seek in a file (Move cursor)*/
//     drv.tell_cb = tell_cb;                 /*Callback to tell the cursor position*/

//     lv_fs_drv_register(&drv);                 /*Finally register the drive*/
// }