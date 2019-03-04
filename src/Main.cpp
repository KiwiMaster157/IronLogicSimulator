#include <SFML/Window.hpp>

#include <iostream>
#include <string_view>
#include <vector>

#include "Args.h"
#include "Console.h"

int main(int argc, char** argv)
{
    iron::Args args(argc, argv, {0,0,1,10});
    switch(args.mode)
    {
        case iron::Args::Mode::CLI:
            iron::cli::Console(args).run();
            break;
        case iron::Args::Mode::GUI:
            break;
        case iron::Args::Mode::DBG:
            iron::cli::Console(args).run();
            break;
        case iron::Args::Mode::VER:
            std::cout << "Fe - " << std::to_string(args.version) << " (c)" << 2019 << std::endl;
            break;
    }

    return 0;
}