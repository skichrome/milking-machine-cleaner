#include "cleaner/CleanHotWaterManager.h"

CleanHotWaterManager::CleanHotWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand)
{
    voidPumpCommand = mVoidPumpCommand;
    milkPumpCommand = mMilkPumpCommand;
    hotWaterCommand = mHotWaterCommand;
    threeWayValveCommand = mThreeWayValveCommand;
}

void CleanHotWaterManager::setup()
{
    state = State::WAITING_START;
}

void CleanHotWaterManager::loop()
{
    switch (state)
    {
    case State::FILLING_WATER:
    {
        fillWater();
        break;
    }
    case State::PAUSE_FILLING_WATER:
    {
        break;
    }
    case State::CLEANING_MACHINE:
    {
        cleanMachine();
        break;
    }
    case State::EVACUATING_WATER:
    {
        evacuateWater();
        break;
    }
    case State::PURGING_WATER:
    {
        purgeWater();
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
    *screenMsg = " Remplissage... ";
    threeWayValveCommand->turnOn();
    hotWaterCommand->turnOn();
    if (waterSensor.isLevelReached())
    {
        hotWaterCommand->turnOff();
        cleanStartMs = millis();
        state = State::CLEANING_MACHINE;
    }
}

void CleanHotWaterManager::cleanMachine()
{
    *screenMsg = "     Lavage     ";
    voidPumpCommand->turnOn();
    if (millis() - cleanStartMs > CLEAN_DURATION_MS)
    {
        evacuationStartMs = millis();
        state = State::EVACUATING_WATER;
    }
}

void CleanHotWaterManager::evacuateWater()
{
    *screenMsg = "   Evacuation   ";
    threeWayValveCommand->turnOff();

    if (millis() - evacuationStartMs > EVACUATION_DURATION_MS)
    {
        purgeStartMs = millis();
        stopVoidPumpStartMs = purgeStartMs + PURGE_DURATION_MS;
        state = State::PURGING_WATER;
    }
}

void CleanHotWaterManager::purgeWater()
{
    *screenMsg = "     purge      ";
    milkPumpCommand->turnOn();
    if (millis() - purgeStartMs > PURGE_DURATION_MS)
    {
        milkPumpCommand->turnOff();

        if (millis() - stopVoidPumpStartMs > STOP_VOID_PUMP_DURATION_MS)
        {
            voidPumpCommand->turnOff();
            state = State::DONE;
        }
    }
}

// --- Public command methods --- //

void CleanHotWaterManager::start(const char **msgToDisplay)
{
    *screenMsg = *msgToDisplay;
    waterSensor.resetSensor();
    state = State::FILLING_WATER;
}

void CleanHotWaterManager::pauseFillingWater()
{
    *screenMsg = "    En pause    ";
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

bool CleanHotWaterManager::isDone()
{
    return state == State::DONE;
}