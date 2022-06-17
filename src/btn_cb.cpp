#include "btn_cb.h"
#include <Arduino.h>
#include "gui/app/mainmenu_app.h"

namespace indrv{
void notify(ButtonEventInfo info){
    if (info.ClickType==ClickType_t::Pressed && info.ButtonId != 2){
        mainmenu_app.notify_indev(info.ButtonId == 1 ? 1 : 2);
    }else if(info.ClickType==ClickType_t::Pressed && info.ButtonId == 2){
        mainmenu_app.notify_indev(0);
    }
}
void btn_handler(ButtonEventInfo info){
    log_d("Got btn%d eventNum%d",info.ButtonId,info.ClickType);
    notify(info);
}

}