#include "main.h"
#include "liblvgl/lvgl.h"

void buildMainButtons(){
    // Create the main buttons for the home screen
    // These buttons will be used to navigate to different screens
    // Create style for the buttons
    static lv_style_t pressing_style;
    lv_style_init(&pressing_style);
    lv_style_set_text_font(&pressing_style, &lv_font_montserrat_30);
    lv_style_set_bg_color(&pressing_style, lv_palette_darken(LV_PALETTE_BLUE, 4));
    //Inside Button Shadow
    lv_style_set_bg_grad_color(&pressing_style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&pressing_style, LV_OPA_10);
    lv_style_set_bg_grad_dir(&pressing_style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&pressing_style, 8);
    lv_style_set_shadow_color(&pressing_style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&pressing_style, -5);
    lv_style_set_shadow_offset_y(&pressing_style, 8);
    lv_style_set_shadow_opa(&pressing_style, LV_OPA_50);


    static lv_style_t main_button_style;
    lv_style_init(&main_button_style);
    lv_style_set_text_font(&main_button_style, &lv_font_montserrat_30);

    //Inside Button Shadow
    lv_style_set_bg_grad_color(&main_button_style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&main_button_style, LV_OPA_10);
    lv_style_set_bg_grad_dir(&main_button_style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&main_button_style, 8);
    lv_style_set_shadow_color(&main_button_style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&main_button_style, -5);
    lv_style_set_shadow_offset_y(&main_button_style, 8);
    lv_style_set_shadow_opa(&main_button_style, LV_OPA_50);

    // CREATE CONTAINER
    // This will be the parent object for all other UI elements
    lv_obj_t* container = lv_obj_create(home_screen);

    //Characteristics of the container
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(container, LV_DIR_NONE);
    lv_obj_set_size(container, 360, 240);
    lv_obj_align(container, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_set_style_pad_all(container, 4, LV_PART_MAIN);
    lv_obj_set_style_radius(container, 0, LV_PART_MAIN);


    // SET GRID LAYOUT
    // LV PCT(50) means 50% of the parent container's width/height
    // Thus creating a 2x2 grid layout
    static int32_t col_dsc[] = {LV_PCT(50), LV_PCT(50), LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {LV_PCT(50), LV_PCT(50), LV_GRID_TEMPLATE_LAST};

    // Assigns the grid layout to the container
    // Sets container's layout to grid
    lv_obj_set_grid_dsc_array(container, col_dsc, row_dsc);
    lv_obj_set_layout(container, LV_LAYOUT_GRID);

    // CREATE BUTTONS
    lv_obj_t* homeButtons[4];

    for (int i = 0; i < 4; i++) {
        // Create a button in container
        // Set the grid position for each button
        homeButtons[i] = lv_button_create(container);
        lv_obj_set_size(homeButtons[i], 160, 100);

        // Position the buttons in the grid
        lv_obj_set_grid_cell(
            homeButtons[i], 
            LV_GRID_ALIGN_CENTER, i % 2, 1,
            LV_GRID_ALIGN_CENTER, i / 2, 1
        );
        // Set the button style
        lv_obj_add_style(homeButtons[i], &main_button_style, 0);
        lv_obj_add_style(homeButtons[i], &pressing_style, LV_STATE_PRESSED);

        // Create a label for each button
        lv_obj_t* label = lv_label_create(homeButtons[i]);
        lv_label_set_text_fmt(label, "Button %d", i + 1);
        lv_obj_center(label);
    }

    // SET BUTTON CALLBACKS

}


lv_obj_t* toggleable[3];
lv_obj_t* toggle_labels[3];
const char* toggleOff[3] = {"Auton: 1", "Red", "Toggle 3"};
const char* toggleOn[3] = {"Auton: 2", "Blue", "Toggle 3"};

void toggleCB(lv_event_t* e){

    // Get the button that was clicked
    lv_obj_t* btn = lv_event_get_target_obj(e);
    int id = (intptr_t)lv_obj_get_user_data(btn);
    // Check if the button is checked
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        // If checked, change the label text
        lv_label_set_text(toggle_labels[id], toggleOn[id]);

        // Set outline style
        //lv_obj_set_style_border_color(toggleable[id], lv_palette_main(LV_PALETTE_INDIGO), LV_PART_MAIN);

    } else {
        // If not checked, change the label text
        lv_label_set_text(toggle_labels[id], toggleOff[id]);
        //lv_obj_set_style_border_color(toggleable[id], lv_palette_darken(LV_PALETTE_BLUE_GREY, 3), LV_PART_MAIN);
    }

    
}


void buildToggles() {
    static lv_style_t team_style;
    lv_style_init(&team_style);
    lv_style_set_text_font(&team_style, &lv_font_montserrat_20);
    lv_style_set_bg_color(&team_style, lv_palette_darken(LV_PALETTE_RED, 3));

     //Inside Button Shadow
    lv_style_set_bg_grad_color(&team_style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&team_style, LV_OPA_10);
    lv_style_set_bg_grad_dir(&team_style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&team_style, 8);
    lv_style_set_shadow_color(&team_style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&team_style, -5);
    lv_style_set_shadow_offset_y(&team_style, 8);
    lv_style_set_shadow_opa(&team_style, LV_OPA_50);

    static lv_style_t toggle_button_style;
    lv_style_init(&toggle_button_style);
    lv_style_set_text_font(&toggle_button_style, &lv_font_montserrat_20);
    
    
    //Inside Button Shadow
    lv_style_set_bg_grad_color(&toggle_button_style, lv_palette_darken(LV_PALETTE_BLUE_GREY, 3));
    lv_style_set_bg_grad_opa(&toggle_button_style, LV_OPA_10);
    lv_style_set_bg_grad_dir(&toggle_button_style, LV_GRAD_DIR_VER);

    // SET SHADOW
    lv_style_set_shadow_width(&toggle_button_style, 8);
    lv_style_set_shadow_color(&toggle_button_style, lv_palette_darken(LV_PALETTE_GREY, 4));
    lv_style_set_shadow_offset_x(&toggle_button_style, -5);
    lv_style_set_shadow_offset_y(&toggle_button_style, 8);
    lv_style_set_shadow_opa(&toggle_button_style, LV_OPA_50);

    // Create a container for switches
    lv_obj_t* switchContainer = lv_obj_create(home_screen);

        // Characteristics of the switch container
    lv_obj_set_scrollbar_mode(switchContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(switchContainer, LV_DIR_NONE);
    lv_obj_set_size(switchContainer, 120, 240);
    lv_obj_align(switchContainer, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_all(switchContainer, 4, LV_PART_MAIN);
    lv_obj_set_style_radius(switchContainer, 0, LV_PART_MAIN);
    // SET GRID LAYOUT
    static int32_t col_dsc[] = {LV_PCT(100), LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {LV_PCT(33), LV_PCT(33), LV_PCT(33), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_grid_dsc_array(switchContainer, col_dsc, row_dsc);
    lv_obj_set_layout(switchContainer, LV_LAYOUT_GRID);

    // CREATE TOGGLEABLES
    
    static int ids[3] = {0, 1, 2};
    for (int i = 0; i < 3; i++) {
        toggleable[i] = lv_button_create(switchContainer);
        lv_obj_set_size(toggleable[i], 100, 70);

        lv_obj_set_grid_cell(toggleable[i], 
            LV_GRID_ALIGN_CENTER, 0, 1, 
            LV_GRID_ALIGN_CENTER, i, 1);
            
        //Make them toggleable
        lv_obj_set_user_data(toggleable[i], (void*)(intptr_t)i);

        lv_obj_add_flag(toggleable[i], LV_OBJ_FLAG_CHECKABLE);

        if (ids[i] == 1){
            lv_obj_add_style(toggleable[i], &team_style, 0);
        } else {
            lv_obj_add_style(toggleable[i], &toggle_button_style, 0);
        }




        // Set outline style
        /*
        lv_obj_set_style_border_width(toggleable[i], 3, LV_PART_MAIN);
        lv_obj_set_style_border_color(toggleable[i], lv_palette_darken(LV_PALETTE_GREY, 3), LV_PART_MAIN);
        lv_obj_set_style_border_opa(toggleable[i], LV_OPA_COVER, LV_PART_MAIN);  // fully opaque border
        lv_obj_set_style_border_side(toggleable[i], LV_BORDER_SIDE_FULL, LV_PART_MAIN);  // full border on all sides
        lv_obj_set_style_radius(toggleable[i], 8, LV_PART_MAIN);
        */
        

        // Create a label for each toggleable
        toggle_labels[i] = lv_label_create(toggleable[i]);
        lv_label_set_text(toggle_labels[i], toggleOff[i]);
        lv_obj_center(toggle_labels[i]);

        lv_obj_add_event_cb(toggleable[i], toggleCB, LV_EVENT_VALUE_CHANGED, &ids[i]);
    }
        
}
void buildHomeScreen() {
    buildMainButtons();
    buildToggles();
}