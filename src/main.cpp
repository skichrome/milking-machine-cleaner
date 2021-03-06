#include <Arduino.h>

#include "Config.h"

#include "menu/MenuManager.h"
#include "inputs/NavigationMenuBtn.h"
#include "inputs/ConfirmMenuBtn.h"

// Menu
MenuManager menuManager = MenuManager();
NavigationMenuBtn navMenuBtn = NavigationMenuBtn(NAV_MENU_BTN_PIN, &menuManager);
ConfirmMenuBtn confirmMenuBtn = ConfirmMenuBtn(CONFIRM_MENU_BTN_PIN, &menuManager);

void setup()
{
  menuManager.setup();
  navMenuBtn.setup();
  confirmMenuBtn.setup();
}

void loop()
{
  menuManager.loop();
  navMenuBtn.loop();
  confirmMenuBtn.loop();
}