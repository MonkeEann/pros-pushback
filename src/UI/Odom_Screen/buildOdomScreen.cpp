#include "UI/buildOdomScreen.hpp"
#include "UI/uiGlobals.hpp"
#include "subsystems/subGlobals.hpp"
extern "C" {
    //#include "UI/pushbackfield.h"
}

const char* poseTexts[3] = {"X: 0.00 in", "Y: 0.00 in", "A: 0.00 deg"};
lv_obj_t* poseLabels[3];

void poseTimer(lv_timer_t* timer) {
    currentPose = monkeChassis.getPose();
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "X: %.2f", currentPose.x);
    lv_label_set_text(poseLabels[0], buffer);

    snprintf(buffer, sizeof(buffer), "Y: %.2f", currentPose.y);
    lv_label_set_text(poseLabels[1], buffer);
 
    snprintf(buffer, sizeof(buffer), "A: %.2f", currentPose.theta);
    lv_label_set_text(poseLabels[2], buffer);

}

void buildOdomScreen() {
    screenSetup(odom_screen);

    lv_obj_t* odomContainer = lv_obj_create(odom_screen);
    containerStyle(odomContainer);
    lv_obj_set_size(odomContainer, LV_PCT(100), LV_PCT(80));

    lv_obj_set_layout(odomContainer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(odomContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(odomContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t* poseContainer = lv_obj_create(odomContainer);
    containerStyle(poseContainer);
    lv_obj_set_size(poseContainer, LV_PCT(100), LV_PCT(100));

    lv_obj_set_layout(poseContainer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(poseContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(poseContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    static lv_style_t style;
    lv_style_init(&style);

    //Inside Label Shadow
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&style, LV_OPA_30);
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&style, -5);
    lv_style_set_shadow_offset_y(&style, 8);
    lv_style_set_shadow_opa(&style, LV_OPA_50);

    for (int i = 0; i < 3; i++){
        poseLabels[i] = lv_label_create(poseContainer);
        lv_label_set_text(poseLabels[i], poseTexts[i]);
        lv_obj_set_style_text_font(poseLabels[i], &lv_font_montserrat_24, 0);
        lv_obj_set_width(poseLabels[i], LV_PCT(100));
        lv_obj_set_style_text_align(poseLabels[i], LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_add_style(poseLabels[i], &style, 0);
        }    
        lv_timer_create(poseTimer, 100, NULL);
}

