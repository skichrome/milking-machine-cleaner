#ifndef CLEAN_COLD_WATER_MANAGER_H
#define CLEAN_COLD_WATER_MANAGER_H

#include "Config.h"

#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"
#include "commands/ColdWaterCommand.h"
#include "commands/HotWaterCommand.h"
#include "commands/ThreeWayValveCommand.h"
#include "inputs/WaterSensor.h"

class CleanColdWaterManager
{
private:
    enum State
    {
        WAITING_START,
        PRE_HEAT_WATER,
        FILLING_WATER,
        COOLDOWN_AFTER_FILL,
        PAUSE_FILLING_WATER,
        CLEANING_MACHINE,
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

    void preHeatHotWater();
    void fillWater();
    void cleanMachine();
    void purgeWater();
    void setSecondLineMessage(unsigned long remainingTime);

    bool isDryingRequired;

    const char **firstLineMsg;
    const char **secondLineMsg;
    String tmpSecondLineStr;

    unsigned long cooldownMs = 0uL;
    unsigned long preHeatHotWaterStartMs = 0uL;
    unsigned long cleanStartMs = 0uL;
    unsigned long purgeStartMs = 0uL;

public:
    CleanColdWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand);

    void setup();
    void loop();

    void start(const bool mIsPreHeatRequired, const bool isDryingRequired, const char **mFirstLineMsg, const char **mSecondLineMsg);
    void pauseFillingWater();
    void resumeFillingWater();
    bool isStarted();
    bool isFillingPaused();
    bool isDone();
    void resetIfDone();
};

#endif