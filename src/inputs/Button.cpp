#include "inputs/Button.h"

Button::Button(byte mPin)
{
    pin = mPin;
}

void Button::setup()
{
    pinMode(pin, INPUT_PULLUP);
    state = ButtonState::RELEASED;
}

void Button::loop()
{
    switch (state)
    {
    case ButtonState::RELEASED:
    {
        bool buttonState = !digitalRead(pin);
        if (buttonState)
            state = ButtonState::PRESSED;
        break;
    }
    case ButtonState::PRESSED:
    {
        onButtonPressed();
        lastAntiBounceTimeMs = millis();
        state = ButtonState::ANTI_BOUNCE;
        break;
    }
    case ButtonState::ANTI_BOUNCE:
    {
        if (millis() - lastAntiBounceTimeMs > ANTI_BOUNCE_TIME_MS && digitalRead(pin))
            state = ButtonState::RELEASED;
        break;
    }

    default:
        break;
    }
}