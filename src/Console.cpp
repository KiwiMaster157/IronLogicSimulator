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
        this->prompt = L"Fe" + std::to_wstring(ver.major) + L">>>";
    else    // Derecated
        this->prompt = L"Fe" + std::to_wstring(ver.major) + L".Debug>>>";

    /*

    this->commands.emplace("exit", Command(
            "exit",
            [](std::istream &in, std::ostream &out, std::vector<std::string> &args){
                return 0;
            }
            ));
    this->commands.emplace("help", Command(
            "help",
            [](std::istream &in, std::ostream &out, std::vector<std::string> &args){
                out << "HELP PAGE" << std::endl;
                return 0;
            }
            ));
    this->commands.emplace("add", Command(
            "add"
            ))
    */

}

int Console::run()
{
    flash();
    bool run = true;
    run = false; // Deprecated - just prevents infinite loop
    std::wstringstream ss;
    do
    {
        // Get input
        *sout << prompt;
        std::wstring input;
        std::getline(*sin, input);

        // Reformat for parsing
        ss.str(input);
        std::vector<std::wstring> cmd;
        while(ss.rdbuf()->in_avail())
        {
            std::wstring token;
            ss >> token;
            cmd.push_back(token);
        }

        // Parse
    } while (run);
    return 0;
}

void Console::help()
{
    *sout << L"\nHELP PAGE" << std::endl;
}

void Console::flash()
{
    *sout << L"\n";
    *sout << L"Fe - " << std::to_wstring(ver);
    *sout << L"\n" << std::endl;
}

}
}