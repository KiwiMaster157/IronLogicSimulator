#pragma once

#include "../../KiwiGUI/KiwiGui.h"

#include <string>

namespace iron
{

//Central entity containing simulation logic.
class Iron;

//Contains the state of a scripted components.
class State;

struct StateID;

//Defines the behavior of both scripted and subcircuit components.
class Behavior;

struct Instruction;

using BehaviorID = std::string;
using Script = std::vector<Instruction>;

//Containes the state of a wire collection.
class WireState;

class Wire;

using WireID = int;

}