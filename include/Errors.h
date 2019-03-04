#pragma once

#include "CoreCircuit.h"

namespace iron
{

enum class ErrorCode
{
    NoError,
    NotFound,
    NegativeIndex,
    IndexExcedesBounds,
    SignalDimensionMismatch,
    InputOccupied,
    UuidTaken,
    BehaviorNotFound
};



class Reporter
{
public:
    Reporter() = default;
    Reporter(std::ostream& stream, short verbosity);
    Reporter(const std::string& filename, short verbosity);

    ~Reporter();

    //Reporting
    void notFound(UUID missing);
    void negativeIndex(int index);
    void indexExcedesBounds(int index, int limit);
    //void signalDimensionMismatch([...]);
    //void inputOccupied([...]);
    void uuidTaken(UUID taken);
    void behaviorNotFound(const std::string& name);

private:
    std::ostream* m_log = nullptr;
    bool m_owning = false;
    short m_verbosity = 0;
};
}