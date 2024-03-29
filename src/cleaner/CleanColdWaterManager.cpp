#include "cleaner/CleanColdWaterManager.h"

CleanColdWaterManager::CleanColdWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand)
{
    voidPumpCommand = mVoidPumpCommand;
    milkPumpCommand = mMilkPumpCommand;
    coldWaterCommand = mColdWaterCommand;
    hotWaterCommand = mHotWaterCommand;
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
    case State::PRE_HEAT_WATER:
    {
        preHeatHotWater();
        break;
    }
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
            state = State::CLEANING_MACHINE;
        }
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

void CleanColdWaterManager::preHeatHotWater()
{
    *firstLineMsg = "  Prechauffage  ";
    setSecondLineMessage(PRE_HEAT_HOT_WATER_PIPE_MS - (millis() - preHeatHotWaterStartMs));

    threeWayValveCommand->turnOff();
    hotWaterCommand->turnOn();

    if (millis() - preHeatHotWaterStartMs > PRE_HEAT_HOT_WATER_PIPE_MS)
    {
        hotWaterCommand->turnOff();
        state = State::FILLING_WATER;
    }
}

void CleanColdWaterManager::fillWater()
{
    *firstLineMsg = " Remplissage... ";
    *secondLineMsg = "                ";
    threeWayValveCommand->turnOff();
    coldWaterCommand->turnOn();
    if (waterSensor.isLevelReached())
    {
        coldWaterCommand->turnOff();
        hotWaterCommand->turnOff();
        cooldownMs = millis();
        state = State::COOLDOWN_AFTER_FILL;
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
        cooldownMs = purgeStartMs + PURGE_DURATION_MS;
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
        cooldownMs = millis();
        state = State::COOLDOWN_AFTER_PURGE;
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

void CleanColdWaterManager::start(const bool mIsPreHeatRequired, const bool mIsDryingRequired, const char **mFirstLineMsg, const char **mSecondLineMsg)
{
    isDryingRequired = mIsDryingRequired;
    firstLineMsg = mFirstLineMsg;
    secondLineMsg = mSecondLineMsg;
    waterSensor.resetSensor();

    if (mIsPreHeatRequired)
    {
        preHeatHotWaterStartMs = millis();
        state = State::PRE_HEAT_WATER;
    }
    else
        state = State::FILLING_WATER;
}

void CleanColdWaterManager::pauseFillingWater()
{
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

bool CleanColdWaterManager::isFillingPaused()
{
    return state == State::PAUSE_FILLING_WATER;
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