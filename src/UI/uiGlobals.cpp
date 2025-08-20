#include "UI/uiGlobals.hpp"

pros::Task* lvglTask = nullptr;
pros::Task* printPIDTask = nullptr;

lv_obj_t *home_screen = nullptr;
lv_obj_t *odom_screen = nullptr;
lv_obj_t *pid_screen = nullptr;

lv_obj_t *terminal_screen = nullptr;
lv_obj_t *terminalTextArea = nullptr;

lv_obj_t *medic_screen = nullptr;

void containerStyle(lv_obj_t* parent){
    lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(parent, LV_DIR_NONE);
    lv_obj_align(parent, LV_ALIGN_TOP_LEFT, 0, 0);
    
    lv_obj_set_style_pad_top(parent, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(parent, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(parent, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_opa(parent, LV_OPA_0, LV_PART_MAIN);
}

void buttonSetup(lv_obj_t* parent){
    static lv_style_t style;
    lv_style_init(&style);

    //Inside Button Shadow
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&style, LV_OPA_30);
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&style, 8);
    lv_style_set_shadow_color(&style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&style, -5);
    lv_style_set_shadow_offset_y(&style, 8);
    lv_style_set_shadow_opa(&style, LV_OPA_50);

    lv_obj_add_style(parent, &style, 0);

    static lv_style_t pressing_style;
    lv_style_init(&pressing_style);

    lv_style_set_bg_color(&pressing_style, lv_palette_darken(LV_PALETTE_BLUE, 4));

    lv_obj_add_style(parent, &pressing_style, LV_STATE_PRESSED);    
}

void screenSetup(lv_obj_t* parent){

    lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(parent, LV_DIR_NONE);
    
    lv_obj_set_style_bg_color(parent, lv_palette_darken(LV_PALETTE_BLUE_GREY, 4), 0);
    lv_obj_set_style_bg_grad_color(parent, lv_color_hex(0x040035), 0);
    lv_obj_set_style_bg_grad_dir(parent, LV_GRAD_DIR_VER, 0);

    lv_obj_set_style_pad_all(parent, 5, 0);

    buildFooter(parent);
}

void buildFooter(lv_obj_t *parent)
{

    // Create a footer that will remain at the bottom of every screen
    /* Init footer and style */
    lv_obj_t *footer = lv_obj_create(parent);

    lv_obj_set_style_text_font(footer, &modak_24, 0);

    lv_obj_set_scrollbar_mode(footer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(footer, LV_DIR_NONE);

    lv_obj_set_size(footer, 460, 60);
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, 10);

    lv_obj_set_style_bg_color(footer, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3), 0);
    lv_obj_set_style_bg_grad_color(footer, lv_color_hex(0x040035), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(footer, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_bg_opa(footer, LV_OPA_COVER, 0);

    lv_obj_set_style_outline_opa(footer, LV_OPA_TRANSP, LV_PART_MAIN);

    lv_obj_set_style_shadow_color(footer, lv_palette_darken(LV_PALETTE_GREY, 4), LV_PART_MAIN);
    lv_obj_set_style_shadow_width(footer, 15, LV_PART_MAIN);
    lv_obj_set_style_shadow_offset_y(footer, -8, LV_PART_MAIN);
    lv_obj_set_style_shadow_opa(footer, LV_OPA_50, LV_PART_MAIN);

    lv_obj_set_style_pad_all(footer, 4, LV_PART_MAIN);
    lv_obj_set_style_radius(footer, 15, LV_PART_MAIN);

    /* Init the default state style */
    static lv_style_t exit_style;
    lv_style_init(&exit_style);
    lv_style_set_bg_opa(&exit_style, LV_OPA_0);
    lv_style_set_align(&exit_style, LV_ALIGN_CENTER);
    lv_style_set_size(&exit_style, 215, 40);
    lv_style_set_text_font(&exit_style, &modak_40);

    /* Init the pressed state style */
    static lv_style_t exit_pressed_style;
    lv_style_init(&exit_pressed_style);

    lv_style_set_outline_width(&exit_pressed_style, 100);
    lv_style_set_outline_color(&exit_pressed_style, lv_palette_darken(LV_PALETTE_BLUE, 4));
    lv_style_set_outline_opa(&exit_pressed_style, LV_OPA_TRANSP);

    lv_style_set_translate_y(&exit_pressed_style, 5);
    lv_style_set_shadow_offset_y(&exit_pressed_style, 3);
    
    static lv_style_transition_dsc_t exit_transition;
    static lv_style_prop_t exit_props[] = {
        LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&exit_transition, exit_props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&exit_pressed_style, &exit_transition);

    /* Init Button and Add Style*/
    lv_obj_t *exit_button = lv_button_create(footer);
    lv_obj_add_style(exit_button, &exit_style, LV_STATE_DEFAULT);
    lv_obj_add_style(exit_button, &exit_pressed_style, LV_STATE_PRESSED);

    /* Init Labels */
    lv_obj_t *exit_label = lv_label_create(exit_button);
    lv_label_set_text(exit_label, "MonkeBots");
    lv_obj_align(exit_label, LV_ALIGN_CENTER, 0, -2);

    lv_obj_t *footer_label_Left = lv_label_create(footer);
    lv_label_set_text(footer_label_Left, "9922z");
    lv_obj_align(footer_label_Left, LV_ALIGN_LEFT_MID, 30, -2);

    lv_obj_t *footer_label_Right = lv_label_create(footer);
    lv_label_set_text(footer_label_Right, "9922z");
    lv_obj_align(footer_label_Right, LV_ALIGN_RIGHT_MID, -30, -2);

    // In order for the event to be triggered when the button is pressed, we need to add an event callback
    lv_obj_add_event_cb(exit_button, exitButtonCb, LV_EVENT_CLICKED, NULL);
}

void exitButtonCb(lv_event_t *e)
{
    /*
    The exit button's purpose is to appear on every screen and return the user to the home screen if pressed.
    */
    lv_obj_t *btn = lv_event_get_target_obj(e);
    lv_screen_load_anim(home_screen, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
}
