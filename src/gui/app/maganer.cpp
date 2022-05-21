// app will have a class/struct.
// the manager will manage running, similar to robomaster code, will have states and exits.
// running app can ask for switching app with provided app_ptr also passing a intent ptr.

#include "maganer.h"
#include "app.h"
#include "mainmenu_app.h"
static app* now_app = nullptr;
static bool inited = false;
/**
 * @brief should be called first
 * 
 */
void manager_init(){
    if (inited)
        return;
    // now_app = mainmenuapp's address
}

void manager_handle(){
    
}