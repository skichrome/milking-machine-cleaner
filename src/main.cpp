#include <Arduino.h>

#include "menu/MenuManager.h"
#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"

MenuManager menuManager = MenuManager();

// Commands
#define VOID_PUMP_PIN 28
#define MILK_PUMP_PIN 30

VoidPumpCommand voidPumpCommand = VoidPumpCommand(VOID_PUMP_PIN);
MilkPumpCommand milkPumpCommand = MilkPumpCommand(MILK_PUMP_PIN);

void setup()
{
  menuManager.setup();
  voidPumpCommand.setup();
  milkPumpCommand.setup();
}

void loop()
{
  menuManager.loop();
  voidPumpCommand.loop();
  milkPumpCommand.loop();
}