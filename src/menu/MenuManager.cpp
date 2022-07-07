#include "menu/MenuManager.h"

void MenuManager::setup()
{
    lcd.init();
    lcd.backlight();
}

void MenuManager::loop()
{
    if(millis() - startTimeMs > 1000)
    {
        lcd.print("TEST");
        startTimeMs = millis();
    }
    else
    {
        lcd.print(emptyLine);
    }
}

void MenuManager::changeSelection()
{
}

void MenuManager::confirmSelection()
{
}