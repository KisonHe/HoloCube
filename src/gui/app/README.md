## Rules
1. apps MUST NOT call any lvgl related function EXCEPT in `init`,`handle`,`deinit`. 
2. manager will not try to delete the app_t's pointer. The app subclass instance life cycle should be managed by the app itself. 
3. virtual class app_t's constructor will push it self to the app_list so other apps list menu-app can know about other apps in system. make sure you call app_t's constructor if you want to add yourself. In case you want a hidden app that can only open with intent, just call app_t with false parameters. You can have multi instance of same app but this is not tested a lot
4. manager will pass a `lv_obj` to app for screen. apps must not clear it, manager will clear it. app also should not draw anything except on the passed obj.
5. apps can ask for switching to another app, see intent for details
6. Internet net stuff. To reduce heat plan to sleep. So... how apps use wifi need some plans, still thinking about it
7. Watch out that the constructor execution order is not defined.