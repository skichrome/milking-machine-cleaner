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
        CLEANING_MACHINE,
        EVACUATING_WATER,
        PURGING_WATER,
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

    unsigned long cleanStartMs = 0L;
    unsigned long evacuationStartMs = 0L;
    unsigned long purgeStartMs = 0L;
    unsigned long stopVoidPumpStartMs = 0L;

public:
    CleanHotWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand);

    void setup();
    void loop();

    void start(const bool coldWaterMode, const char **mFirstLineMsg, const char **mSecondLineMsg);
    void pauseFillingWater();
    void resumeFillingWater();
    bool isStarted();
    bool isDone();
    void resetIfDone();
};

#endif