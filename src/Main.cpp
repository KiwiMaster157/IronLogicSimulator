#include <SFML/Window.hpp>

#include <iostream>
#include <string_view>
#include <vector>
#include <glog/logging.h>

#include "Args.h"
#include "Console.h"

int main(int argc, char** argv)
{
    google::InitGoogleLogging("Fe");
    LOG(INFO) << "Hello";
    // Increment Major on incompatible change (0 = unstable)
    // Increment Minor on release
    // Increment Build on build
    // Increment Rev on class/function/method scale changes or issue resolution
    iron::Args args(argc, argv, {0,0,1,5});

    switch(args.mode)
    {
        case iron::Args::Mode::CLI:
            iron::cli::Console(args).run();
            break;
        case iron::Args::Mode::GUI:
            std::cerr << "Fe - " << std::to_string(args.version) << " does not currently have graphics support." << std::endl;
            std::cerr << "Use 'Fe -c' for the Command Line Interface" << std::endl;
            break;
        case iron::Args::Mode::DBG:     // Deprecated
            iron::cli::Console(args).run();
            break;
        case iron::Args::Mode::VER:
            std::cout << "Fe - " << std::to_string(args.version) << " (c)" << 2019 << std::endl;
            break;
    }

    return 0;
}