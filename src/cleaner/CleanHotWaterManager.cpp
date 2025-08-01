#include "cleaner/CleanHotWaterManager.h"

CleanHotWaterManager::CleanHotWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand)
{
    voidPumpCommand = mVoidPumpCommand;
    milkPumpCommand = mMilkPumpCommand;
    coldWaterCommand = mColdWaterCommand;
    hotWaterCommand = mHotWaterCommand;
    threeWayValveCommand = mThreeWayValveCommand;
}

void CleanHotWaterManager::setup()
{
    waterSensor.setup();
    state = State::WAITING_START;

    // Todo: TMP Evacuation mode
    //pinMode(PIN_RGB_LED_RED, OUTPUT);
    //digitalWrite(PIN_RGB_LED_RED, ledState);
}

void CleanHotWaterManager::loop()
{
    waterSensor.loop();

    switch (state)
    {
    case State::FILLING_WATER:
    {
        fillWater();
        break;
    }
    case State::PAUSE_FILLING_WATER:
    {
        *firstLineMsg = "    En pause    ";
        coldWaterCommand->turnOff();
        hotWaterCommand->turnOff();
        break;
    }
    case State::COOLDOWN_AFTER_FILL:
    {
        *firstLineMsg = "Fin remplissage ";
        if (millis() - cooldownMs > DELAY_BETWEEN_TWO_COMMAND_MS)
        {
            cleanStartMs = millis();
            milkPumpDelay = millis();
            state = State::CLEANING_MACHINE;
        }
        break;
    }
    case State::CLEANING_MACHINE:
    {
        cleanMachine();
        if(millis() - milkPumpDelay > DELAY_HOT_WATER_MILK_PUMP_START)
            milkPumpCommand->turnOn();
        break;
    }
    case State::EVACUATING_WATER:
    {
        milkPumpCommand->turnOff();
        evacuateWater();
        break;
    }
    case State::PURGING_WATER:
    {
        purgeWater();
        break;
    }
    case State::COOLDOWN_AFTER_PURGE:
    {
        *firstLineMsg = " Temporisation  ";
        if (millis() - cooldownMs > DELAY_BETWEEN_TWO_COMMAND_MS)
        {
            voidPumpCommand->turnOff();
            cooldownMs = millis();
            state = State::FINAL_COOLDOWN;
        }
        break;
    }
    case State::FINAL_COOLDOWN:
    {
        *firstLineMsg = "      Fin       ";
        if (millis() - cooldownMs > DELAY_BETWEEN_TWO_COMMAND_MS)
        {
            state = State::DONE;
        }
        break;
    }

    default:
    {
        break;
    }
    }
}

// --- Private methods --- //

void CleanHotWaterManager::fillWater()
{
    *firstLineMsg = " Remplissage... ";
    *secondLineMsg = "                ";
    threeWayValveCommand->turnOn();

    if (coldMode)
        coldWaterCommand->turnOn();
    else
        hotWaterCommand->turnOn();

    if (waterSensor.isLevelReached())
    {
        coldWaterCommand->turnOff();
        hotWaterCommand->turnOff();

        cooldownMs = millis();
        state = State::COOLDOWN_AFTER_FILL;
    }
}

void CleanHotWaterManager::cleanMachine()
{
    *firstLineMsg = "     Lavage     ";
    setSecondLineMessage(CLEAN_HOT_WATER_DURATION_MS - (millis() - cleanStartMs));

    voidPumpCommand->turnOn();
    if (millis() - cleanStartMs > CLEAN_HOT_WATER_DURATION_MS)
    {
        evacuationStartMs = millis();
        state = State::EVACUATING_WATER;
    }
}

void CleanHotWaterManager::evacuateWater()
{
    *firstLineMsg = "   Evacuation   ";
    setSecondLineMessage(EVACUATION_DURATION_MS - (millis() - evacuationStartMs));

    threeWayValveCommand->turnOff();

    if (millis() - evacuationStartMs > EVACUATION_DURATION_MS)
    {
        purgeStartMs = millis();
        cooldownMs = purgeStartMs + PURGE_DURATION_MS;
        state = State::PURGING_WATER;
    }
}

void CleanHotWaterManager::purgeWater()
{
    *firstLineMsg = "     purge      ";
    setSecondLineMessage(PURGE_DURATION_MS - (millis() - purgeStartMs));

    milkPumpCommand->turnOn();
    if (millis() - purgeStartMs > PURGE_DURATION_MS)
    {
        milkPumpCommand->turnOff();
        cooldownMs = millis();
        state = State::COOLDOWN_AFTER_PURGE;
    }
}

void CleanHotWaterManager::setSecondLineMessage(unsigned long remainingTime)
{
    unsigned long m = remainingTime / 1000uL / 60uL;
    remainingTime = remainingTime % (1000uL * 60uL);
    unsigned long s = remainingTime / 1000uL;

    if (m > 100 || s > 100)
        return;

    if (m < 10 && s < 10)
        tmpSecondLineStr = "      0" + String(m) + ":0" + String(s) + "     ";
    else if (m < 10 && s >= 10)
        tmpSecondLineStr = "      0" + String(m) + ":" + String(s) + "     ";
    else if (m >= 10 && s < 10)
        tmpSecondLineStr = "       " + String(m) + ":0" + String(s) + "    ";
    else
        tmpSecondLineStr = "       " + String(m) + ":" + String(s) + "    ";

    *secondLineMsg = tmpSecondLineStr.c_str();
}

// --- Public command methods --- //

void CleanHotWaterManager::start(const bool coldWaterMode, const char **mFirstLineMsg, const char **mSecondLineMsg)
{
    coldMode = coldWaterMode;
    firstLineMsg = mFirstLineMsg;
    secondLineMsg = mSecondLineMsg;
    waterSensor.resetSensor();
    state = State::FILLING_WATER;
}

void CleanHotWaterManager::pauseFillingWater()
{
    if (state == State::FILLING_WATER)
        state = State::PAUSE_FILLING_WATER;
}

void CleanHotWaterManager::resumeFillingWater()
{
    if (state == State::PAUSE_FILLING_WATER)
    {
        waterSensor.resetSensor();
        state = State::FILLING_WATER;
    }
}

bool CleanHotWaterManager::isStarted()
{
    return state != State::WAITING_START;
}

bool CleanHotWaterManager::isFillingPaused()
{
    return state == State::PAUSE_FILLING_WATER;
}

bool CleanHotWaterManager::isDone()
{
    return state == State::DONE;
}

void CleanHotWaterManager::resetIfDone()
{
    if (state == State::DONE)
        state = State::WAITING_START;
}