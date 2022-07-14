#ifndef HOT_WATER_COMMAND_H
#define HOT_WATER_COMMAND_H

#include "RelayCommand.h"

class HotWaterCommand : public RelayCommand
{
public:
    HotWaterCommand(uint8_t mPin) : RelayCommand(mPin){};
};

#endif