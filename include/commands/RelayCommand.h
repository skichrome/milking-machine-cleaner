#ifndef RELAY_COMMAND_H
#define RELAY_COMMAND_H

#include <Arduino.h>

class RelayCommand
{
private:
    byte pin;

    enum RelayState
    {
        ENABLED = LOW,
        DISABLED = HIGH
    } relayState;

    RelayState previousState;

public:
    RelayCommand(byte mPin);

    void setup();
    void loop();

    bool isRelayOn();
    void switchRelay(bool newState);
};

#endif