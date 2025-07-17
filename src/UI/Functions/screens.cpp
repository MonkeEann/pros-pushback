#include "main.h"
#include "liblvgl/lvgl.h"

static void btnCb(lv_event_t* e) {
    lv_obj_t* btn = lv_event_get_target_obj(e);
    lv_label_set_text(lv_obj_get_child(btn, 0), "Button Pressed!");
    //lv_screen_load(odom_screen);
}

void homeScreen() {
    buildHomeScreen();
}
void odomScreen() {
    lv_obj_t* btn = lv_button_create(odom_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Odom Screen");
    lv_obj_center(label);
}

void pidScreen() {
    lv_obj_t* btn = lv_button_create(pid_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "PID Screen");
    lv_obj_center(label);
}

void terminalScreen() {
    lv_obj_t* btn = lv_button_create(terminal_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Terminal Screen");
    lv_obj_center(label);
}

void medicScreen() {
    lv_obj_t* btn = lv_button_create(medic_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Medic Screen");
    lv_obj_center(label);
}