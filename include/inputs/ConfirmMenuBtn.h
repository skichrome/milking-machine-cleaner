#ifndef CONFIRM_MENU_BTN_H
#define CONFIRM_MENU_BTN_H

#include "Button.h"
#include "menu/MenuManager.h"

class ConfirmMenuBtn : public Button
{
private:
    MenuManager *menu;

protected:
    void onButtonPressed();

public:
    ConfirmMenuBtn(uint8_t mPin, MenuManager *mMenu) : Button(mPin), menu(mMenu){};
};

#endif