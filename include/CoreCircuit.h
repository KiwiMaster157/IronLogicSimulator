#pragma once

#include "Script.h"
#include "Signal.h"

#include <vector>

namespace iron
{

using UUID = unsigned long long; 

namespace core
{

struct Pin
{
    UUID uuid;
    short index;
};

struct Connection
{
    Pin source;
    Pin destination;
};

struct Behavior
{
    Script f;
    std::vector<short> inputSizes;
    std::vector<short> outputSizes;
    std::vector<short> internalSizes;
};

struct Port
{
    Signal value;
    std::vector<UUID> destinations;
};

struct State
{
    Behavior* behavior;
    //or 
    //std::string behaviorID;
    std::vector<Pin> inputs;
    std::vector<Port> outputs;
    std::vector<Signal> state;
};

}
}