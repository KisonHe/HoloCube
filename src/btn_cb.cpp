#include "btn_cb.h"
#include <Arduino.h>
#include "gui/app/mainmenu_app.h"
extern mainmenu_app_t mainmenu_app;
namespace indrv{
void btn_handler(ButtonEventInfo info){
    log_w("Got btn%d eventNum%d",info.ButtonId,info.ClickType);
}
void notity(){
    
}
}