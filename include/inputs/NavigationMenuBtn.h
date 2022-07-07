#ifndef NAVIGATION_MENU_BTN_H
#define NAVIGATION_MENU_BTN_H

#include "Button.h"
#include "menu/MenuManager.h"

class NavigationMenuBtn : public Button
{
private:
    MenuManager *menu;

protected:
    void onButtonPressed();

public:
    NavigationMenuBtn(uint8_t mPin, MenuManager *mMenu) : Button(mPin), menu(mMenu){};
};

#endif