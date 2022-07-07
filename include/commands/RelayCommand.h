#ifndef RELAY_COMMAND_H
#define RELAY_COMMAND_H

#include <Arduino.h>

class RelayCommand
{
private:
    uint8_t pin;

    enum RelayState
    {
        ENABLED = LOW,
        DISABLED = HIGH
    } relayState;

    RelayState previousState;

public:
    RelayCommand(uint8_t mPin);

    void setup();
    void loop();

    bool isRelayOn();
    void switchRelay(bool newState);
};

#endif