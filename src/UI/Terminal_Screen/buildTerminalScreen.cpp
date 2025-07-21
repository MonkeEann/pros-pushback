#include "UI/buildTerminalScreen.hpp"
#include "liblvgl/lvgl.h"
#include "UI/uiGlobals.hpp"

void buildTerminalScreen(){
    
    screenSetup(terminal_screen);
    // Creating Container to keep text area within the useable screen area
    lv_obj_t* container = lv_obj_create(terminal_screen);
    
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_set_scroll_dir(container, LV_DIR_NONE);
    lv_obj_set_size(container, 460, 170);
    lv_obj_align(container, LV_ALIGN_TOP_LEFT, 0, 0);
    
    lv_obj_set_style_pad_all(container, 5, LV_PART_MAIN);
    lv_obj_set_style_radius(container, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(container, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_opa(container, LV_OPA_0, LV_PART_MAIN);

    terminalTextArea = lv_textarea_create(container);
    lv_obj_set_style_pad_all(terminalTextArea, 5, 0);
    lv_obj_set_size(terminalTextArea, 450, 160);
    lv_obj_align(terminalTextArea, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(terminalTextArea, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_line_space(terminalTextArea, -2, 0);

    lv_textarea_set_placeholder_text(terminalTextArea, "Robot Messages will appear here!");
    lv_obj_set_style_opa(terminalTextArea, LV_OPA_TRANSP, LV_PART_CURSOR);

}