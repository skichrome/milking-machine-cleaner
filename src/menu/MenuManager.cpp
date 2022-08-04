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
    threeWayValveCommand.setup();

    coldCleanManager.setup();
    hotCleanManager.setup();
    cleanManager.setup();

    lcd.init();
    lcd.backlight();
}

void MenuManager::loop()
{
    voidPumpCommand.loop();
    milkPumpCommand.loop();
    hotWaterCommand.loop();
    coldWaterCommand.loop();
    threeWayValveCommand.loop();

    coldCleanManager.loop();
    hotCleanManager.loop();
    cleanManager.loop();

    if (isInCleanMenu && !cleanManager.isBusy())
        printCleanMenu();
    else if (!isInCleanMenu && !cleanManager.isBusy())
        printMainMenu();
    else
    {
        lcd.home();
        lcd.print(firstLineMessage);
        lcd.setCursor(0, 1);
        lcd.print(secondLineMessage);
    }
}

void MenuManager::changeSelection()
{
    if (isInCleanMenu && !cleanManager.isBusy())
        positionCleanMenu = (positionCleanMenu + 1) % cleanMenuSize;
    else if (!isInCleanMenu && !cleanManager.isBusy())
        positionMainMenu = (positionMainMenu + 1) % mainMenuSize;
}

void MenuManager::confirmSelection()
{
    if (cleanManager.isBusy())
    {
        cleanManager.pauseOrResumeFill();
    }
    else if (isInCleanMenu && !cleanManager.isBusy())
    {
        switch (positionCleanMenu)
        {
        case 0:
        {
            cleanManager.startCleanFromHotWater();
            break;
        }
        case 1:
        {
            cleanManager.startCleanFromFirstRince();
            break;
        }
        case 2:
        {
            cleanManager.startCleanFromSecondRince();
            break;
        }
        case 3:
        {
            cleanManager.startPeraceticClean();
            break;
        }
        case 4:
        {
            cleanManager.startImpactClean();
            break;
        }
        case 5:
        {
            cleanManager.startOnlyHotWaterClean();
            break;
        }
        case 6:
        {
            cleanManager.startOnlyFirstRince();
            break;
        }
        case 7:
        {
            isInCleanMenu = false;
            break;
        }

        default:
            break;
        }
    }
    else if (!isInCleanMenu && !cleanManager.isBusy())
    {
        switch (positionMainMenu)
        {
        case 0: // Normal cleaning
        {
            cleanManager.startNormalClean();
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