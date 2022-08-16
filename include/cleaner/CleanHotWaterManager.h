#ifndef CLEAN_HOT_WATER_MANAGER_H
#define CLEAN_HOT_WATER_MANAGER_H

#include "Config.h"

#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"
#include "commands/ColdWaterCommand.h"
#include "commands/HotWaterCommand.h"
#include "commands/ThreeWayValveCommand.h"
#include "inputs/WaterSensor.h"

class CleanHotWaterManager
{
private:
    enum State
    {
        WAITING_START,
        FILLING_WATER,
        PAUSE_FILLING_WATER,
        COOLDOWN_AFTER_FILL,
        CLEANING_MACHINE,
        EVACUATING_WATER,
        PURGING_WATER,
        COOLDOWN_AFTER_PURGE,
        FINAL_COOLDOWN,
        DONE
    } state;

    VoidPumpCommand *voidPumpCommand;
    MilkPumpCommand *milkPumpCommand;
    ColdWaterCommand *coldWaterCommand;
    HotWaterCommand *hotWaterCommand;
    ThreeWayValveCommand *threeWayValveCommand;

    WaterSensor waterSensor = WaterSensor(WATER_SENSOR_PIN);

    void fillWater();
    void cleanMachine();
    void evacuateWater();
    void purgeWater();
    void setSecondLineMessage(unsigned long remainingTime);

    bool coldMode = false;
    const char **firstLineMsg;
    const char **secondLineMsg;
    String tmpSecondLineStr;

    unsigned long cooldownMs = 0uL;
    unsigned long cleanStartMs = 0uL;
    unsigned long evacuationStartMs = 0uL;
    unsigned long purgeStartMs = 0uL;

    // Todo: TMP manual evacuation mode
    bool isBtnPressed = false;
    bool ledState = true;
    unsigned long ledBlinkStartMs = 0uL;
    const unsigned long LED_BLINK_DURATION_MS = 500uL;

public:
    CleanHotWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand);

    void setup();
    void loop();

    void start(const bool coldWaterMode, const char **mFirstLineMsg, const char **mSecondLineMsg);
    void pauseFillingWater();
    void resumeFillingWater();
    bool isStarted();
    bool isFillingPaused();
    bool isDone();
    void resetIfDone();

    void endEvacuate();
};

#endif