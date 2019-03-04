#pragma once

#include "Script.h"
#include "Signal.h"

#include <vector>

namespace iron
{

//Requirement: std::less<UUID> is well defined
//Requirement: Efficient pass-by-value
using UUID = unsigned long long; 

namespace core
{

struct Pin
{
    UUID uuid;
    short index = -1;
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
    std::vector<Pin> inputs;
    std::vector<Port> outputs;
    std::vector<Signal> state;
};

}
}