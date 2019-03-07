#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <unordered_map>

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

using Action = std::function<int(std::wistream*, std::wostream*, std::vector<std::wstring>&)>;

class Command {
public:
    Command(const std::wstring &name, Action action, std::wistream* in, std::wostream* out) {
        this->name = name;
        this->action = action;
        this->in = in;
        this->out = out;
    }
    int run() {
        return this->action(this->in, this->out, this->args);
    }
    void add_arg(std::wstring &arg) { this->args.push_back(arg); }
    void clear_args() { this->args.clear(); }
    std::wstring &get_name() { return this->name; }
private:
    std::wstring name;
    Action action;
    std::vector<std::wstring> args;
    std::wistream *in;
    std::wostream *out;
};

class Console
{
    private:
        std::wostream *sout = &std::wcout;
        std::wistream *sin = &std::wcin;
        std::wstring prompt;
        Args::Mode mode = Args::Mode::CLI;
        Version ver;
        std::unordered_map<std::wstring,Command> commands;

    public:
        Console(Args args);
        int run();
        void help();
        void flash();
        
};

}
}