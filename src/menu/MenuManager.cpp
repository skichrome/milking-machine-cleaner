#include "menu/MenuManager.h"

void MenuManager::setup()
{
    lcd.init();
    lcd.backlight();
}

void MenuManager::loop()
{
    if (isInCleanMenu)
        printCleanMenu();
    else
        printMainMenu();
}

void MenuManager::changeSelection()
{
    if (isInCleanMenu)
        positionCleanMenu = (positionCleanMenu + 1) % cleanMenuSize;
    else
        positionMainMenu = (positionMainMenu + 1) % mainMenuSize;
}

void MenuManager::confirmSelection()
{
    if (isInCleanMenu)
    {
        switch (positionCleanMenu)
        {
        case 0: // Start from hot water
        {
            break;
        }
        case 6: // Back
        {
            isInCleanMenu = false;
            break;
        }

        default:
            break;
        }
    }
    else
    {
        switch (positionMainMenu)
        {
        case 0: // Normal cleaning
        {
            break;
        }
        case 1: // Other cleaning
        {
            positionCleanMenu = 0;
            isInCleanMenu = true;
            break;
        }

        default:
            break;
        }
    }
}

void MenuManager::printMainMenu()
{
    lcd.home();
    lcd.print(mainTitles[positionMainMenu]);
    lcd.setCursor(0, 1);
    lcd.print(mainSubTitles[positionMainMenu]);
}

void MenuManager::printCleanMenu()
{
    lcd.home();
    lcd.print(cleanTitles[positionCleanMenu]);
    lcd.setCursor(0, 1);
    lcd.print(cleanSubTitles[positionCleanMenu]);
}