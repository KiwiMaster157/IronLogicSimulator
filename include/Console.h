#include <iostream>
#include <string>
#include <sstream>

#include "Args.h"

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

class Console
{
    private:
        ::std::ostream &sout = ::std::cout;
        ::std::istream &sin = ::std::cin;
        ::std::string prompt;
        Args::Mode mode = Args::Mode::CLI;
        Version ver;

    public:
        Console(Args args);
        int run();
        void flash();
        
};

}
}