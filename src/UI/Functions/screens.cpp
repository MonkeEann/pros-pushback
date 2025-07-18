#include "main.h"
#include "liblvgl/lvgl.h"

void homeScreen() {
    buildHomeScreen();
}
void odomScreen() {

    buildFooter(odom_screen);

    lv_obj_t* btn = lv_button_create(odom_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Odom Screen");
    lv_obj_center(label);

}

void pidScreen() {

    buildFooter(pid_screen);

    lv_obj_t* btn = lv_button_create(pid_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "PID Screen");
    lv_obj_center(label);
}

void terminalScreen() {

    buildFooter(terminal_screen);

    lv_obj_t* btn = lv_button_create(terminal_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Terminal Screen");
    lv_obj_center(label);
}

void medicScreen() {

    buildFooter(medic_screen);

    lv_obj_t* btn = lv_button_create(medic_screen);
    lv_obj_set_size(btn, 200, 50);
    lv_obj_center(btn);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Medic Screen");
    lv_obj_center(label);
}