#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_MAX_LENGTH 16

class MenuManager
{
private:
    const char *titles[17] = {"Demarrer lavage?", "   Eau Froide   ", "Eau Chaude", "Pompe a vide", "Pompe a lait"};
    const char *menuLine = "";
    const char *emptyLine = "                ";

    unsigned int positionMenu = 0;

    bool isChangeRequested = false;
    bool isConfirmRequested = false;

    LiquidCrystal_I2C lcd;
    long startTimeMs = 0L;

public:
    MenuManager() : lcd(0x27, LCD_MAX_LENGTH, 2)
    {
    }

    void setup();
    void loop();

    void changeSelection();
    void confirmSelection();
};

#endif