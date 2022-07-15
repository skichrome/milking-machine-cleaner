#ifndef THREE_WAY_VALVE_COMMAND_H
#define THREE_WAY_VALVE_COMMAND_H

#include "RelayCommand.h"

class ThreeWayValveCommand : public RelayCommand
{
public:
    ThreeWayValveCommand(uint8_t mPin) : RelayCommand(mPin){};
};

#endif