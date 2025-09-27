#include "UI/buildMedicScreen.hpp"
#include "UI/uiGlobals.hpp"
#include "subsystems/subGlobals.hpp"
#include <cmath>

lv_obj_t* motorInfoContainers[10];
lv_obj_t* motorTA[10];
const char* motorLabels[10] = {
    "L Drive Motor 1 \n", 
    "L Drive Motor 2\n", 
    "L Drive Motor 3\n", 
    "R Drive Motor 1\n", 
    "R Drive Motor 2\n",
    "R Drive Motor 3\n", 
    "Intake Motor\n",
    "Back Roller Motor\n",
    "Hoard Motor\n",
    "Top Roller Motor\n"};

double temperatures[10] = {
    intakeMotor.get_temperature(), 
    backRollersMotor.get_temperature(), 
    hoardMotor.get_temperature(), 
    topRollerMotor.get_temperature()};

int32_t voltage[10] = {
    intakeMotor.get_voltage(), 
    backRollersMotor.get_voltage(), 
    hoardMotor.get_voltage(), 
    topRollerMotor.get_voltage()    
};

int32_t current[10] = {
    intakeMotor.get_current_draw(), 
    backRollersMotor.get_current_draw(), 
    hoardMotor.get_current_draw(), 
    topRollerMotor.get_current_draw()    
};

void buildMedicScreen(){
    screenSetup(medic_screen);
    buildFooter(medic_screen);

    lv_obj_t* setupContainer = lv_obj_create(medic_screen);
    containerStyle(setupContainer);
    lv_obj_set_size(setupContainer, LV_PCT(100), 180);
    lv_obj_set_style_pad_all(setupContainer, 0, 0);
    
    //lv_obj_set_style_opa(setupContainer, LV_OPA_100, 0);
    //lv_obj_set_style_bg_color(setupContainer, lv_palette_main(LV_PALETTE_GREEN), NULL);

    lv_obj_set_layout(setupContainer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(setupContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(setupContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    
    lv_obj_t* containers[2];
    for(int i = 0; i < 2; i++){
        containers[i] = lv_obj_create(setupContainer);
        containerStyle(containers[i]);
        //lv_obj_set_style_bg_opa(containers[i], LV_OPA_30, 0);
        //lv_obj_set_style_bg_color(containers[i], lv_palette_main(LV_PALETTE_RED), 0);
        lv_obj_set_layout(containers[i], LV_LAYOUT_FLEX);
        lv_obj_set_style_pad_all(containers[i], 0, 0);
        
             
    }
    lv_obj_set_size(containers[0], LV_PCT(20), 180);
    lv_obj_set_size(containers[1], LV_PCT(80), 180);

    lv_obj_set_flex_flow(containers[0], LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_flow(containers[1], LV_FLEX_FLOW_ROW_WRAP);
    
    lv_obj_set_flex_align(containers[0], LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);   
    lv_obj_set_flex_align(containers[1], LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    
    lv_obj_set_scrollbar_mode(containers[1], LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_scroll_dir(containers[1], LV_DIR_ALL);
    for (int i = 0; i < 10; i++){
        motorInfoContainers[i] = lv_obj_create(containers[1]);
        lv_obj_set_size(motorInfoContainers[i], LV_PCT(45), LV_PCT(50));lv_obj_set_scrollbar_mode(motorInfoContainers[i], LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_scroll_dir(motorInfoContainers[i], LV_DIR_NONE);

        motorTA[i] = lv_textarea_create(motorInfoContainers[i]);

        lv_obj_set_size(motorTA[i], 165, 85);
        lv_obj_align(motorTA[i], LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_bg_opa(motorTA[i], LV_OPA_0, 0);

        lv_obj_set_scrollbar_mode(motorTA[i], LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_scroll_dir(motorTA[i], LV_DIR_NONE);

        lv_obj_set_style_pad_all(motorTA[i], 0, 0);
        lv_obj_set_style_text_line_space(motorTA[i], 2, 0);
        lv_obj_set_style_opa(motorTA[i], LV_OPA_TRANSP, LV_PART_CURSOR);

    }
    drawLabels();
    
    lv_obj_t* reloadBtn = lv_button_create(containers[0]);
    buttonSetup(reloadBtn);
    lv_obj_set_size(reloadBtn, LV_PCT(100), LV_PCT(50));

    lv_obj_t* btnLabel = lv_label_create(reloadBtn);
    lv_obj_set_style_text_font(btnLabel, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_align(btnLabel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(btnLabel, LV_SYMBOL_REFRESH "\nReload");
    lv_obj_center(btnLabel);

    lv_obj_add_event_cb(reloadBtn, reload_btn_cb, LV_EVENT_CLICKED, NULL);
}

void drawLabels(){
    updateMotorData();
    char buf[32];

    for (int i = 0; i < 10; i++){
        if(!std::isinf(temperatures[i]) && temperatures[i] != 0){
            lv_obj_set_style_text_font(motorTA[i], &lv_font_montserrat_20, 0);
            lv_textarea_set_text(motorTA[i], motorLabels[i]);

            lv_obj_set_style_text_font(motorTA[i], &lv_font_montserrat_12, 0);

            if (temperatures[i] > 60)
            {
                lv_obj_set_style_text_color(motorTA[i], lv_palette_main(LV_PALETTE_RED), 0);

                snprintf(buf, sizeof(buf), "Temp: %.2f C \n", temperatures[i]);
                lv_textarea_add_text(motorTA[i], buf);

                lv_obj_set_style_text_color(motorTA[i], lv_color_hex(0x000000), 0);
            } else {
                snprintf(buf, sizeof(buf), "Temp: %.2f C \n", temperatures[i]);
                lv_textarea_add_text(motorTA[i], buf);
            }
            
            
            snprintf(buf, sizeof(buf), "Voltage: %d mV \n", voltage[i]);
            lv_textarea_add_text(motorTA[i], buf);
            
            snprintf(buf, sizeof(buf), "Current: %d mA \n", current[i]);
            lv_textarea_add_text(motorTA[i], buf);

        }   else {
            lv_obj_set_style_text_font(motorTA[i], &lv_font_montserrat_20, 0);
            lv_textarea_set_text(motorTA[i], motorLabels[i]);

            lv_obj_set_style_text_font(motorTA[i], &lv_font_montserrat_12, 0);
            lv_textarea_add_text(motorTA[i], "DISCONNECTED");
        }
    }
}

void reload_btn_cb(lv_event_t* e){
    drawLabels();
}
void updateMotorData(){
    temperatures[6] = intakeMotor.get_temperature();
    temperatures[7] = backRollersMotor.get_temperature();
    temperatures[8] = hoardMotor.get_temperature();
    temperatures[9] = topRollerMotor.get_temperature();


    voltage[6] = intakeMotor.get_voltage();
    voltage[7] = backRollersMotor.get_voltage();
    voltage[8] = hoardMotor.get_voltage();
    voltage[9] = topRollerMotor.get_voltage();

    current[6] = intakeMotor.get_current_draw();
    current[7] = backRollersMotor.get_current_draw();
    current[8] = hoardMotor.get_current_draw();
    current[9] = topRollerMotor.get_current_draw();
}