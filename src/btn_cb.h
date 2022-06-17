#pragma once
/**
 * @file btn_cb.h
 * @author kisonhe (kisonhepenpal@gmail.com)
 * @brief this file combines the input from 3 axis and btn then notify stuff. the lvgl encoder is 3 buttons and a 3-axis
 *        sensor, with this file source of lib/button can leave unchanged
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "button.h"
namespace indrv{
enum indev_state{
    None,
    Left,
    Right,
    Middle
};
void btn_handler(ButtonEventInfo info);
}
// ButtonEventHandler = [](ButtonEventInfo info){
//     log_d("Got btn%d eventNum%d",info.ButtonId,info.ClickType);
// };