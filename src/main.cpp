#include <Arduino.h>

#include "menu/MenuManager.h"
#include "commands/VoidPumpCommand.h"

MenuManager menuManager = MenuManager();

// Commands
#define VOID_PUMP_PIN 28

VoidPumpCommand voidPumpCommand = VoidPumpCommand(VOID_PUMP_PIN);

void setup()
{
  menuManager.setup();
  voidPumpCommand.setup();
}

void loop()
{
  menuManager.loop();
  voidPumpCommand.loop();
}