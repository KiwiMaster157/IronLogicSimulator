#include "Console.h"

/*
    Pin = Component|UUID[.Port]
    add Type [Component|UUID]
    remove Component|UUID
    connect {Pin Pin} {Pin Pin}
    deconnect {Pin Pin}
    run [Circuit]
    print ???
    help
    Command help
    select Circuit
    config Component|UUID [key [value]]
    load File
    save [File]
    set Pin Value


    _add UUID Type
    _remove UUID
    _connect {UUID.Port UUID.Port}
    _deconnect {UUID.Port UUID.Port}
    _reconnect {UUID.Port UUID.Port} {UUID.Port UUID.Port}
    _set UUID[.Port]
*/

namespace iron {

namespace cli {

Console::Console(Args args)
{
    this->ver = args.version;
    this->mode = args.mode;
    if(mode == Args::Mode::CLI)
        this->prompt = "Fe" + std::to_string(ver.major) + ">>>";
    else
        this->prompt = "Fe" + std::to_string(ver.major) + ".Debug>>>";
}

int Console::run()
{
    flash();
    bool run = true;
    std::stringstream ss;
    do
    {
        sout << prompt;
        std::string input;
        std::getline(sin, input);
        ss.str(input);
        std::vector<std::string> cmd;
        while(ss.rdbuf()->in_avail())
        {
            std::string token;
            ss >> token;
            cmd.push_back(token);
        }
        for(auto part : cmd)
            sout << part << std::endl;
    } while (run);
    return 0;
}

void Console::flash()
{
    sout << "\n";
    sout << "Fe - " << std::to_string(ver);
    sout << "\n" << std::endl;
}

}
}