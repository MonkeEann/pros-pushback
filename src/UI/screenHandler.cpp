#include "UI/screenHandler.hpp"
#include "UI/buildHomeScreen.hpp"
#include "UI/buildTerminalScreen.hpp"
#include "UI/buildPIDScreen.hpp"
#include "UI/buildMedicScreen.hpp"
#include "UI/buildOdomScreen.hpp"

void homeScreen() {
    buildHomeScreen();
}
void odomScreen() {
    buildOdomScreen();

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