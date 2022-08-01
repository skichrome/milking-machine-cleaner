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
    waterSensor.setup();

    state = State::WAITING_START;
}

void CleanColdWaterManager::loop()
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
    *firstLineMsg = " Remplissage... ";
    *secondLineMsg = "                ";
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
    *firstLineMsg = isDryingRequired ? "rincage-sechage " : "     rincage    ";
    setSecondLineMessage((isDryingRequired ? CLEAN_AND_DRY_COLD_WATER_DURATION_MS : CLEAN_COLD_WATER_DURATION_MS) - (millis() - cleanStartMs));

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
    *firstLineMsg = "      purge     ";
    setSecondLineMessage(PURGE_DURATION_MS - (millis() - purgeStartMs));

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

void CleanColdWaterManager::setSecondLineMessage(unsigned long remainingTime)
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

void CleanColdWaterManager::start(const bool mIsDryingRequired, const char **mFirstLineMsg, const char **mSecondLineMsg)
{
    isDryingRequired = mIsDryingRequired;
    firstLineMsg = mFirstLineMsg;
    secondLineMsg = mSecondLineMsg;
    waterSensor.resetSensor();
    state = State::FILLING_WATER;
}

void CleanColdWaterManager::pauseFillingWater()
{
    *firstLineMsg = "    En pause    ";
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

bool CleanColdWaterManager::isStarted()
{
    return state != State::WAITING_START;
}

bool CleanColdWaterManager::isDone()
{
    return state == State::DONE;
}

void CleanColdWaterManager::resetIfDone()
{
    if (state == State::DONE)
        state = State::WAITING_START;
}