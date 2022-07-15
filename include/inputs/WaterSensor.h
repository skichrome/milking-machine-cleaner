#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <Arduino.h>

class WaterSensor
{
private:
    uint8_t pin;

    enum State
    {
        IDLE,
        TRIGGERED
    } state;

public:
    WaterSensor(uint8_t mPin);

    void setup();
    void loop();

    bool isLevelReached();
    void resetSensor();
};

#endif