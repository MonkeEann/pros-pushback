#include "UI/screenHandler.hpp"
#include "UI/buildHomeScreen.hpp"
#include "UI/buildTerminalScreen.hpp"
#include "UI/buildPIDScreen.hpp"
#include "UI/buildMedicScreen.hpp"

void homeScreen() {
    buildHomeScreen();
}
void odomScreen() {
    buildFooter(odom_screen);

}

void pidScreen() {
    buildPIDScreen();

}

void terminalScreen() {
    buildTerminalScreen();

}   

void medicScreen() {
    buildMedicScreen();
}