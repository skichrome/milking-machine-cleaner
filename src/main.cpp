#include <Arduino.h>

#include "menu/MenuManager.h"
#include "inputs/NavigationMenuBtn.h"
#include "inputs/ConfirmMenuBtn.h"
#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"

// Menu
#define NAV_MENU_BTN_PIN 8
#define CONFIRM_MENU_BTN_PIN 9
MenuManager menuManager = MenuManager();
NavigationMenuBtn navMenuBtn = NavigationMenuBtn(NAV_MENU_BTN_PIN, &menuManager);
ConfirmMenuBtn confirmMenuBtn = ConfirmMenuBtn(CONFIRM_MENU_BTN_PIN, &menuManager);

// Commands
#define VOID_PUMP_PIN 28
#define MILK_PUMP_PIN 30

VoidPumpCommand voidPumpCommand = VoidPumpCommand(VOID_PUMP_PIN);
MilkPumpCommand milkPumpCommand = MilkPumpCommand(MILK_PUMP_PIN);

void setup()
{
  menuManager.setup();
  navMenuBtn.setup();
  confirmMenuBtn.setup();

  voidPumpCommand.setup();
  milkPumpCommand.setup();
}

void loop()
{
  menuManager.loop();
  navMenuBtn.loop();
  confirmMenuBtn.loop();

  voidPumpCommand.loop();
  milkPumpCommand.loop();
}