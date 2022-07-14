#ifndef COLD_WATER_COMMAND_H
#define COLD_WATER_COMMAND_H

#include "RelayCommand.h"

class ColdWaterCommand : public RelayCommand
{
public:
    ColdWaterCommand(uint8_t mPin) : RelayCommand(mPin){};
};

#endif