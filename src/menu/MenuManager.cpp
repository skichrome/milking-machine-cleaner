#include "menu/MenuManager.h"

MenuManager::MenuManager()
{
}

void MenuManager::setup()
{
    voidPumpCommand.setup();
    milkPumpCommand.setup();
    hotWaterCommand.setup();
    coldWaterCommand.setup();

    lcd.init();
    lcd.backlight();
}

void MenuManager::loop()
{
    voidPumpCommand.loop();
    milkPumpCommand.loop();
    hotWaterCommand.loop();
    coldWaterCommand.loop();

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
        case 2: // Cold water valve
        {
            coldWaterCommand.switchState();

            // change state display of void pump
            if (coldWaterCommand.isRelayOn())
                mainSubTitles[2] = onLine;
            else
                mainSubTitles[2] = offLine;
            break;
        }
        case 3: // Hot water valve
        {
            hotWaterCommand.switchState();

            // change state display of void pump
            if (hotWaterCommand.isRelayOn())
                mainSubTitles[3] = onLine;
            else
                mainSubTitles[3] = offLine;
            break;
        }
        case 4: // Void pump cmd
        {
            voidPumpCommand.switchState();

            // change state display of void pump
            if (voidPumpCommand.isRelayOn())
                mainSubTitles[4] = onLine;
            else
                mainSubTitles[4] = offLine;
            break;
        }
        case 5: // Milk pump cmd
        {
            milkPumpCommand.switchState();

            // Change state display of milk pump
            if (milkPumpCommand.isRelayOn())
                mainSubTitles[5] = onLine;
            else
                mainSubTitles[5] = offLine;
            break;
        }

        default:
            break;
        }
    }
}

void MenuManager::printMainMenu()
{
    if (screenMsg == nullptr)
    {
        // todo : ?
    }

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