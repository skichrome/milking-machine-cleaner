#ifndef CLEAN_COLD_WATER_MANAGER_H
#define CLEAN_COLD_WATER_MANAGER_H

#include "Config.h"

#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"
#include "commands/ColdWaterCommand.h"
#include "commands/ThreeWayValveCommand.h"
#include "inputs/WaterSensor.h"

class CleanColdWaterManager
{
private:
    enum State
    {
        WAITING_START,
        FILLING_WATER,
        PAUSE_FILLING_WATER,
        CLEANING_MACHINE,
        PURGING_WATER,
        DONE
    } state;

    VoidPumpCommand *voidPumpCommand;
    MilkPumpCommand *milkPumpCommand;
    ColdWaterCommand *coldWaterCommand;
    ThreeWayValveCommand *threeWayValveCommand;

    WaterSensor waterSensor = WaterSensor(WATER_SENSOR_PIN);

    void fillWater();
    void cleanMachine();
    void purgeWater();

    bool isDryingRequired;

    const char **firstLineMsg;
    const char **secondLineMsg;

    unsigned long cleanStartMs = 0L;
    unsigned long purgeStartMs = 0L;
    unsigned long stopVoidPumpStartMs = 0L;

public:
    CleanColdWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, ColdWaterCommand *mColdWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand);

    void setup();
    void loop();

    void start(const bool isDryingRequired, const char **mFirstLineMsg, const char **mSecondLineMsg);
    void pauseFillingWater();
    void resumeFillingWater();
    bool isStarted();
    bool isDone();
    void resetIfDone();
};

#endif