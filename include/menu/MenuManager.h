#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_I2C_ADDRESS 0x3F
#define LCD_MAX_LENGTH 16

class MenuManager
{
private:
    const char *mainTitles[17] =     {" Lavage normal  ", " Autres lavages ", "   Eau Froide   ", "   Eau Chaude   ", "  Pompe a vide  ", "  Pompe a lait  "};
    const char *mainSubTitles[17] =  {"       -->      ", "       -->      ", "       off      ", "       off      ", "       off      ", "       off      "};
    const char *cleanTitles[17] =    {" Depart depuis  ", " Depart depuis  ", " Depart depuis  ", " Lavage de choc ", "Eau chaude seule", "1er rincage seul", "     Retour     "};
    const char *cleanSubTitles[17] = {"   eau chaude   ", "  1er rincage   ", "  2nd rincage   ", "       -->      ", "       -->      ", "       -->      ", "       <--      "};
    const char *emptyLine = "                ";

    const unsigned int mainMenuSize = 6;
    const unsigned int cleanMenuSize = 7;
    unsigned int positionMainMenu = 0;
    unsigned int positionCleanMenu = 0;

    bool isInCleanMenu = false;

    LiquidCrystal_I2C lcd;
    long startTimeMs = 0L;

    void printMainMenu();
    void printCleanMenu();

public:
    MenuManager() : lcd(LCD_I2C_ADDRESS, LCD_MAX_LENGTH, 2) {}

    void setup();
    void loop();

    void changeSelection();
    void confirmSelection();
};

#endif