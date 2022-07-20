#include "cleaner/CleanColdWaterManager.h"

CleanColdWaterManager::CleanColdWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand)
{
    voidPumpCommand = mVoidPumpCommand;
    milkPumpCommand = mMilkPumpCommand;
    coldWaterCommand = mColdWaterCommand;
    threeWayValveCommand = mThreeWayValveCommand;
}

void CleanColdWaterManager::setup()
{
    state = State::WAITING_START;
}

void CleanColdWaterManager::loop()
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

void CleanColdWaterManager::fillWater()
{
    screenMsg = " Remplissage... ";
    threeWayValveCommand->turnOff();
    coldWaterCommand->turnOn();
    if (waterSensor.isLevelReached())
    {
        coldWaterCommand->turnOff();
        cleanStartMs = millis();
        state = State::CLEANING_MACHINE;
    }
}

void CleanColdWaterManager::cleanMachine()
{
    screenMsg = "     Lavage     ";
    voidPumpCommand->turnOn();

    if (millis() - cleanStartMs > (isDryingRequired ? CLEAN_AND_DRY_COLD_WATER_DURATION_MS : CLEAN_COLD_WATER_DURATION_MS))
    {
        purgeStartMs = millis();
        stopVoidPumpStartMs = purgeStartMs + PURGE_DURATION_MS;
        state = State::PURGING_WATER;
    }
}

void CleanColdWaterManager::purgeWater()
{
    screenMsg = "     purge      ";
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

void CleanColdWaterManager::start(const bool mIsDryingRequired, const char *msgToDisplay)
{
    isDryingRequired = mIsDryingRequired;
    screenMsg = msgToDisplay;
    waterSensor.resetSensor();
    state = State::FILLING_WATER;
}

void CleanColdWaterManager::pauseFillingWater()
{
    screenMsg = "    En pause    ";
    if (state == State::FILLING_WATER)
        state = State::PAUSE_FILLING_WATER;
}

void CleanColdWaterManager::resumeFillingWater()
{
    if (state == State::PAUSE_FILLING_WATER)
    {
        waterSensor.resetSensor();
        state = State::FILLING_WATER;
    }
}

bool CleanColdWaterManager::isDone()
{
    return state == State::DONE;
}