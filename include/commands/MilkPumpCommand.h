#ifndef MILK_PUMP_COMMAND_H
#define MILK_PUMP_COMMAND_H

#include "RelayCommand.h"

class MilkPumpCommand : public RelayCommand
{
public:
    MilkPumpCommand(byte mPin) : RelayCommand(mPin){};
};

#endif