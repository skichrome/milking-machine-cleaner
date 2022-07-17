#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Config.h"

#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"
#include "commands/ColdWaterCommand.h"
#include "commands/HotWaterCommand.h"
#include "commands/ThreeWayValveCommand.h"

class MenuManager
{
private:
    const char *onLine =    "     marche     ";
    const char *offLine =   "     arret      ";
    const char *emptyLine = "                ";

    const char *mainTitles[17] =     {" Lavage normal  ", " Autres lavages ", "   Eau Froide   ", "   Eau Chaude   ", "  Pompe a vide  ", "  Pompe a lait  "};
    const char *mainSubTitles[17] =  {"       -->      ", "       -->      ",      offLine      ,      offLine      ,      offLine      ,      offLine      };
    const char *cleanTitles[17] =    {" Depart depuis  ", " Depart depuis  ", " Depart depuis  ", "  peracetique   ", " Lavage de choc ", "Eau chaude seule", "1er rincage seul", "     Retour     "};
    const char *cleanSubTitles[17] = {"   eau chaude   ", "  1er rincage   ", "  2nd rincage   ", "       -->      ", "       -->      ", "       -->      ", "       -->      ", "       <--      "};

    const unsigned int mainMenuSize = 6;
    const unsigned int cleanMenuSize = 8;
    unsigned int positionMainMenu = 0;
    unsigned int positionCleanMenu = 0;

    bool isInCleanMenu = false;

    VoidPumpCommand voidPumpCommand = VoidPumpCommand(VOID_PUMP_PIN);
    MilkPumpCommand milkPumpCommand = MilkPumpCommand(MILK_PUMP_PIN);
    ColdWaterCommand coldWaterCommand = ColdWaterCommand(COLD_WATER_PIN);
    HotWaterCommand hotWaterCommand = HotWaterCommand(HOT_WATER_PIN);
    ThreeWayValveCommand threeWayValveCommand = ThreeWayValveCommand(THREE_WAY_VALVE_PIN);

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