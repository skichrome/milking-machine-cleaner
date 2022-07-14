#include "commands/RelayCommand.h"

RelayCommand::RelayCommand(uint8_t mPin)
{
    pin = mPin;
}

void RelayCommand::setup()
{
    relayState = RelayCommand::DISABLED;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, relayState);
}

void RelayCommand::loop()
{
    if (previousState != relayState)
    {
        digitalWrite(pin, relayState);
        previousState = relayState;
    }
}

bool RelayCommand::isRelayOn()
{
    if (relayState == RelayState::ENABLED)
        return true;
    else
        return false;
}

void RelayCommand::switchRelay(bool newState)
{
    if (newState)
        relayState = RelayState::ENABLED;
    else
        relayState = RelayState::DISABLED;
}

void RelayCommand::turnOn()
{
    if (relayState == RelayState::DISABLED)
        switchRelay(true);
}

void RelayCommand::turnOff()
{
    if (relayState == RelayState::ENABLED)
        switchRelay(false);
}

void RelayCommand::switchState()
{
    if (relayState == RelayState::ENABLED)
        turnOff();
    else
        turnOn();
}