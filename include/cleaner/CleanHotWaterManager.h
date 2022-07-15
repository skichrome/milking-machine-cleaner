#ifndef CLEAN_HOT_WATER_MANAGER_H
#define CLEAN_HOT_WATER_MANAGER_H

#include "commands/VoidPumpCommand.h"
#include "commands/MilkPumpCommand.h"
#include "commands/HotWaterCommand.h"
#include "commands/ThreeWayValveCommand.h"
#include "inputs/WaterSensor.h"

#define WATER_SENSOR_PIN A7

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
    HotWaterCommand *hotWaterCommand;
    ThreeWayValveCommand *threeWayValveCommand;

    WaterSensor waterSensor = WaterSensor(WATER_SENSOR_PIN);

    void fillWater();
    void cleanMachine();
    void evacuateWater();
    void purgeWater();

    const char **screenMsg;
    unsigned long cleanStartMs = 0L;
    const unsigned long CLEAN_DURATION_MS = 8L * 60L * 1000L;

    unsigned long evacuationStartMs = 0L;
    const unsigned long EVACUATION_DURATION_MS = 1 * 60L * 1000L;

    unsigned long purgeStartMs = 0L;
    const unsigned long PURGE_DURATION_MS = 7L * 1000L;

    unsigned long stopVoidPumpStartMs = 0L;
    const unsigned long STOP_VOID_PUMP_DURATION_MS = 1L * 1000L;

public:
    CleanHotWaterManager(VoidPumpCommand *mVoidPumpCommand, MilkPumpCommand *mMilkPumpCommand, HotWaterCommand *mHotWaterCommand, ThreeWayValveCommand *mThreeWayValveCommand);

    void setup();
    void loop();

    void start(const char **msgToDisplay);
    void pauseFillingWater();
    void resumeFillingWater();
    bool isDone();
};

#endif