#include "UI/buildPIDScreen.hpp"
#include "UI/uiGlobals.hpp"
#include "roboConfig.hpp"
#include "classDefine.hpp"
#include <cmath>


lv_obj_t* PIDlabels[6];
lv_obj_t* PIDbuttons[6];
lv_obj_t* modeToggleBtn;
bool isAdditionMode = true;

lv_obj_t* incrementButtons[3];
int selectedIncrementIndex = 0;

PID* pids[2] = {&drivePID, &PID1};

double prevValues[6] = {0};
double currentIncrement = 0;

void initPrevValues(){
    for (int i = 0; i < 6; i++){
        prevValues[i] = -100;
    }
}
void PIDScreenInit(){
    initPrevValues();
    lv_timer_create(printPIDScreenTaskFn, 100, nullptr);
}

const char* pidLabels[2][3] = {
    {"kP: %.3f", "kI: %.3f", "kd: %.3f"},
    {"kP: %.3f", "kI: %.3f", "kd: %.3f"}
};

struct PIDEditContext {
    PID* pid;
    int paramIndex;
};

void adjustPIDCallback(lv_event_t* e) {
    if (!LIVE_TUNING) return;
    PIDEditContext* ctx = static_cast<PIDEditContext*>(lv_event_get_user_data(e));
    if (!ctx) return;

    double delta = isAdditionMode ? currentIncrement : -currentIncrement;
    double kP = ctx->pid->getkP();
    double kI = ctx->pid->getkI();
    double kD = ctx->pid->getkD();

    switch (ctx->paramIndex){
        case 0: kP += delta; break;
        case 1: kI += delta; break;
        case 2: kD += delta; break;
    }

    // Set the new constants
    ctx->pid->setConstants(kP, kI, kD);
    
    printf("PID updated: pid=%p param=%d -> kP=%.3f, kI=%.3f, kD=%.3f\n", ctx->pid, ctx->paramIndex, kP, kI, kD);
}


void buildPIDScreen(){
    screenSetup(pid_screen);
    buildFooter(pid_screen);

    lv_obj_t* setupContainer = lv_obj_create(pid_screen);
    containerStyle(setupContainer);
    lv_obj_set_size(setupContainer, LV_PCT(100), 180);
    lv_obj_set_style_pad_all(setupContainer, 0, 0);

    lv_obj_set_layout(setupContainer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(setupContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(setupContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    
    lv_obj_t* incrementContainer = lv_obj_create(setupContainer);
    lv_obj_set_style_pad_all(incrementContainer, 0, 0);
    buildIncrementContainer(incrementContainer);


    lv_obj_t* containers[2];
    const char* labels[2] = {"Drive PID", "PID 1"};

    for (int i = 0; i < 2; i++)
    {
        containers[i] = lv_obj_create(setupContainer);
        containerStyle(containers[i]);
        lv_obj_set_layout(containers[i], LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(containers[i], LV_FLEX_FLOW_COLUMN);
        lv_obj_set_size(containers[i], LV_PCT(40), 180);
        
        lv_obj_t* title = lv_label_create(containers[i]);
        lv_label_set_text(title, labels[i]);
        lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
        // lv_obj_set_style_pad_bottom(title, 5, 0);
        lv_obj_set_width(title, LV_PCT(100));
        lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);

    }

    

    for (int i = 0; i < 6; i++){
        PIDbuttons[i] = lv_button_create(containers[i/3]); //Integer Division -- less than 3 puts into container 0, and more than in 1
        buttonSetup(PIDbuttons[i]);
        lv_obj_set_size(PIDbuttons[i], LV_PCT(100), 35);

        PIDlabels[i] = lv_label_create(PIDbuttons[i]);
        lv_obj_center(PIDlabels[i]);

        PIDEditContext* ctx = new PIDEditContext{pids[i/3], i % 3};
        lv_obj_add_event_cb(PIDbuttons[i], adjustPIDCallback, LV_EVENT_CLICKED, ctx);

    }


}
void buildIncrementContainer(lv_obj_t* parent){
    const char* increments[] = {"0.001", "0.01", "0.1"};

    containerStyle(parent);
    lv_obj_set_size(parent, LV_PCT(20), LV_PCT(100));
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for(int i = 0; i < 3; i++){
        incrementButtons[i] = lv_button_create(parent);
        buttonSetup(incrementButtons[i]);
        lv_obj_set_size(incrementButtons[i], LV_PCT(100), LV_PCT(20));
        //lv_obj_set_style_pad_all(incrementButtons[i], 0, LV_PART_MAIN);

        lv_obj_t* label = lv_label_create(incrementButtons[i]);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
        lv_label_set_text(label, increments[i]);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

        lv_obj_add_event_cb(incrementButtons[i], increment_btn_cb, LV_EVENT_CLICKED, (void*)(intptr_t)i);
    }
    currentIncrement = 0.001;
    lv_obj_set_style_bg_color(incrementButtons[selectedIncrementIndex], lv_palette_darken(LV_PALETTE_BLUE,4), 0);

    modeToggleBtn = lv_button_create(parent);
    buttonSetup(modeToggleBtn);
    lv_obj_set_size(modeToggleBtn, LV_PCT(100), LV_PCT(20));

    lv_obj_t* toggleLabel = lv_label_create(modeToggleBtn);
    lv_label_set_text(toggleLabel, "Add");
    lv_obj_set_style_text_font(toggleLabel, &lv_font_montserrat_18, 0);
    lv_obj_set_style_text_align(toggleLabel, LV_TEXT_ALIGN_RIGHT, 0);

    lv_obj_add_event_cb(modeToggleBtn, toggle_mode_cb, LV_EVENT_CLICKED, NULL);

}
void increment_btn_cb(lv_event_t* e){
    int index = (intptr_t)lv_event_get_user_data(e);
    selectedIncrementIndex = index;

    for (int i = 0; i < 3; i++ ){
        lv_obj_set_style_bg_color(incrementButtons[i], i == index ? lv_palette_darken(LV_PALETTE_BLUE, 4) : lv_palette_darken(LV_PALETTE_BLUE_GREY, 3), 0);
    }
    const char* selectedText = lv_label_get_text(lv_obj_get_child(incrementButtons[index], 0));
    currentIncrement = atof(selectedText);
}
void toggle_mode_cb(lv_event_t* e){
    isAdditionMode = !isAdditionMode;

    lv_obj_t* label = lv_obj_get_child(modeToggleBtn, 0);
    lv_label_set_text(label, isAdditionMode ? "Add" : "Sub");
}
void printPIDScreenTaskFn(lv_timer_t* timer){
    char buffer[32];
    
    for (int i = 0; i < 6; i++) {
        int pidIndex = i / 3;
        int constIndex = i % 3;

        double value;
        switch (constIndex) {
            case 0: value = pids[pidIndex]->getkP(); break;
            case 1: value = pids[pidIndex]->getkI(); break;
            case 2: value = pids[pidIndex]->getkD(); break;
            default: break;
        }

        if (fabs(value - prevValues[i]) > 0.0001) {  // update if changed
            prevValues[i] = value;
            snprintf(buffer, sizeof(buffer), pidLabels[pidIndex][constIndex], value);
            if (PIDlabels[i]) lv_label_set_text(PIDlabels[i], buffer);
        }
    }
    //printf("updated PID screen\n");
}