#include "commands/RelayCommand.h"

RelayCommand::RelayCommand(byte mPin)
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