#pragma once

#include "CoreCircuit.h"

#include <map>
#include <set>
#include <thread>

namespace iron
{
namespace core
{

enum class ErrorCode
{
    NoError,
    NotFound,
    NegativeIndex,
    IndexExcedesBounds,
    SignalDimensionMismatch,
    InputOccupied
};

class Simulator
{
public:
    //Components
    bool checkUUID(UUID lookup) const;//Returns true if lookup is available

    ErrorCode addComponent(const std::string& behavior, UUID lookup);

    ErrorCode removeComponent(UUID lookup);

    ErrorCode touch(UUID lookup);
    ErrorCode modifyInternal(UUID lookup, int index, const Signal& value);
    ErrorCode modifyInternalQuiet(UUID lookup, int index, const Signal& value);

    std::pair<const Signal&, ErrorCode> peekInternal(UUID lookup, int index) const;
    
    std::pair<const Signal&, ErrorCode> peekOutput(UUID lookup, short index) const;
    std::pair<const Signal&, ErrorCode> peekOutput(Pin output) const;
    
    std::pair<const Signal&, ErrorCode> peekInput(UUID lookup, short index) const;
    std::pair<const Signal&, ErrorCode> peekInput(Pin input) const;

    //Connections
    ErrorCode addConnection(Pin source, Pin destination);
    ErrorCode addConnection(const Connection& connect);

    ErrorCode removeConnection(Pin source, Pin destination);
    ErrorCode removeConnection(const Connection& connect);

    ErrorCode moveConnection(Pin source, Pin destination, Pin newSoucre, Pin newDestination);
    ErrorCode moveConnection(const Connection& connect, const Connection& newConnect);

    ErrorCode moveConnectionSource(Pin source, Pin destination, Pin newSource);
    ErrorCode moveConnectionSource(const Connection& connect, Pin newSource);

    ErrorCode moveConnectionDestination(Pin source, Pin destination, Pin newDestination);
    ErrorCode moveConnectionDestination(const Connection& connect, Pin newDestination);

    //Simulation



    //Miscellaneous
    void errorFormatting(std::ostream* target, const std::string& format);

private:
    std::vector<std::thread> m_threadPool;
    std::map<UUID, State> m_substates;
    std::map<std::string, Behavior> m_types;

    std::set<UUID> m_emptying;
    std::set<UUID> m_filling;

    const Signal m_defaultReturn;
};

}
}