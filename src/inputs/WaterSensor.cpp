#include "inputs/WaterSensor.h"

WaterSensor::WaterSensor(uint8_t mPin)
{
    pin = mPin;
}

void WaterSensor::setup()
{
    pinMode(pin, INPUT);
    state = State::IDLE;
}

void WaterSensor::loop()
{
    if (state == State::IDLE && digitalRead(pin))
        state = State::TRIGGERED;
}

bool WaterSensor::isLevelReached()
{
    return state == State::TRIGGERED;
}

void WaterSensor::resetSensor()
{
    state = State::IDLE;
}
