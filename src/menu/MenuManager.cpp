#include "menu/MenuManager.h"

void MenuManager::setup()
{
    lcd.init();
    lcd.backlight();

    lcd.home();
    lcd.print("BOOT");
}

void MenuManager::loop()
{
    lcd.home();
    lcd.print(titles[positionMenu]);
}

void MenuManager::changeSelection()
{
    positionMenu = (positionMenu + 1) % menuSize;
}

void MenuManager::confirmSelection()
{
}