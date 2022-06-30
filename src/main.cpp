#include <Arduino.h>

#include "menu/MenuManager.h"

MenuManager menuManager = MenuManager();

void setup()
{
  menuManager.setup();
}

void loop()
{
  menuManager.loop();
}