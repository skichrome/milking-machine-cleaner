#ifndef VOID_PUMP_COMMAND_H
#define VOID_PUMP_COMMAND_H

#include "RelayCommand.h"

class VoidPumpCommand : public RelayCommand
{
public:
    VoidPumpCommand(uint8_t mPin) : RelayCommand(mPin){};
};

#endif