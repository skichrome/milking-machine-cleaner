#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
private:
    uint8_t pin;

    enum ButtonState
    {
        PRESSED,
        RELEASED,
        ANTI_BOUNCE
    } state;

    unsigned long lastPressedTimeMs = 0L;
    unsigned long lastAntiBounceTimeMs = 0L;

    const unsigned long PRESSED_MINIMUM_TIME_MS = 50;
    const unsigned long ANTI_BOUNCE_TIME_MS = 100;

protected:
    virtual void onButtonPressed();

public:
    Button(uint8_t mPin);

    void setup();
    void loop();
};

#endif