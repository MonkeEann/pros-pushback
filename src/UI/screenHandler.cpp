#include "UI/screenHandler.hpp"
#include "UI/buildHomeScreen.hpp"
#include "UI/buildTerminalScreen.hpp"

void homeScreen() {
    buildHomeScreen();
}
void odomScreen() {
    buildFooter(odom_screen);

}

void pidScreen() {
    buildFooter(pid_screen);

}

void terminalScreen() {
    buildTerminalScreen();

}   

void medicScreen() {
    buildFooter(medic_screen);

}