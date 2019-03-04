#pragma once

#include <string>
#include <vector>

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
    std::string arg3 = 0;
};

using Script = std::vector<Instruction>;

}
}