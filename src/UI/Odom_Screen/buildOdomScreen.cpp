#include "UI/buildOdomScreen.hpp"
#include "UI/uiGlobals.hpp"
extern "C" {
    //#include "UI/pushbackfield.h"
}
void buildOdomScreen() {
    screenSetup(odom_screen);

    LV_IMAGE_DECLARE(Push_Back_Field);
    lv_obj_t *fieldImg = lv_image_create(odom_screen);
    lv_image_set_src(fieldImg, &Push_Back_Field);
    lv_obj_align(fieldImg, LV_ALIGN_CENTER, 0, 0);
    
}