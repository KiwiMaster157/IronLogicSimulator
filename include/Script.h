#pragma once

#include <string>
#include <vector>

#include "Signal.h"

namespace iron
{
namespace core
{
    
struct Instruction
{
    ///Pull list from document at school!!!
    enum OpCode
    {
        And,
        AndI,

        End
    } code;

    int arg1 = 0;
    int arg2 = 0;
    int arg3 = 0;
    Signal argv;
};

using Script = std::vector<Instruction>;

}
}