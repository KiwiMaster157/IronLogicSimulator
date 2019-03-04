#pragma once

#include "Version.h"

#include <vector>
#include <string_view>
#include <iostream>

/*
    fe -[OPTIONS] [FILE]
    -c --console
    -d --debug
    -g --graphics
    -v --verbose
    --version
*/

namespace iron{

struct Args
{
    enum Mode
    {
        CLI,    //
        GUI,    //
        DBG,    //CLI-Enables hidden features for testing
        VER
    } mode = Mode::GUI;
    std::string_view program;
    bool verbose;
    Version version;

    Args() = delete;

    Args(int argc, char** argv, Version ver)
    {
        this->version = ver;
        std::vector<std::string_view> args;
        for(int i = 0; i < argc; i++)
            args.push_back(argv[i]);
        
        this->program = args[0];
        
        // -c --console
        // [file]

        for(auto a : args)
        {
            if(a == "-c" || a == "--console")
                this->mode = Mode::CLI;
            else if(a == "-d" || a == "--degug")
                this->mode = Mode::DBG;
            else if(a == "-g" || a == "--graphics")
                this->mode = Mode::GUI;
            else if(a == "--version")
                this->mode = Mode::VER;
            else if(a == "-v" || a == "--verbose")
                this->verbose = true;
        }
    }
};

}