#pragma once

#include "Errors.h"

#include <string>
#include <string_view>
#include <vector>

namespace iron
{

struct Voltage
{
    enum Level : char
    {
        Null,   //N n
        Float,  //F f X x
        High,   //1
        Low,    //0
        Error,  //E R
        PullHigh,   //^
        PullLow,    //v
        PullError   //e r
    } level = Level::Null;

    Voltage() = default;
    Voltage(Level initial) noexcept;
};

struct Signal
{
    std::vector<Voltage> data;

    Signal() = default;
    Signal(const Signal&) = default;
    Signal(Signal&&) = default;

    Signal& operator=(Signal src);

    Signal(int size, Voltage initial);

    int size() const;

    Voltage& operator[](int index);
    const Voltage& operator[](int index) const;
};

//Limits output to Float, High, Low, Error
Voltage normalize(Voltage value) noexcept;
Signal normalize(const Signal& value);

Signal str2sig(std::string_view str);
std::string sig2str(const Signal& sig);

template<Voltage operation(Voltage, Voltage) noexcept>
ErrorCode signalOp(Signal& destination, const Signal& lhs, const Signal& rhs) noexcept
{
    if(!(destination.size() == lhs.size() && lhs.size() == rhs.size())
    {
        //let caller report error
        return ErrorCode::SignalDimensionMismatch;
    }

    for(int i = 0; i < lhs.size(); i++)
    {
        destination[i] = operation(lhs[i], rhs[i]);
    }

    return ErrorCode::NoError;
}

template<Voltage operation(Voltage) noexcept>
ErrorCode signalOp(Signal& destination, const Signal& arg) noexcept
{
    if(!(destination.size() == arg.size()))
    {
        //let caller report error
        return ErrorCode::SignalDimensionMismatch;
    }

    for(int i = 0; i < arg.size(); i++)
    {
        destination[i] = arg[i];
    }

    return ErrorCode::NoError;
}

bool operator==(Voltage, Voltage) noexcept;
bool operator!=(Voltage, Voltage) noexcept;

bool operator==(const Signal&, const Signal&);
bool operator!=(const Signal&, const Signal&);

Voltage andVoltage(Voltage lhs, Voltage rhs) noexcept;
Voltage orVoltage(Voltage lhs, Voltage rhs) noexcept;
Voltage xorVoltage(Voltage lhs, Voltage rhs) noexcept;
Voltage mergeVoltage(Voltage lhs, Voltage rhs) noexcept;

Voltage inverseVoltage(Voltage arg) noexcept;

/*
Voltage operator&(Voltage, Voltage) noexcept;
Voltage operator|(Voltage, Voltage) noexcept;
Voltage operator^(Voltage, Voltage) noexcept;
Voltage operator%(Voltage, Voltage) noexcept;

Voltage& operator&=(Voltage&, Voltage);
Voltage& operator|=(Voltage&, Voltage);
Voltage& operator^=(Voltage&, Voltage);
Voltage& operator%=(Voltage&, Voltage);

Signal operator&(const Signal&, const Signal&);
Signal operator|(const Signal&, const Signal&);
Signal operator^(const Signal&, const Signal&);
Signal operator%(const Signal&, const Signal&);

Signal& operator&=(Signal&, const Signal&);
Signal& operator|=(Signal&, const Signal&);
Signal& operator^=(Signal&, const Signal&);
Signal& operator%=(Signal&, const Signal&);

Signal operator&(const Signal&, Voltage);
Signal operator|(const Signal&, Voltage);
Signal operator^(const Signal&, Voltage);
Signal operator%(const Signal&, Voltage);

Signal& operator&=(Signal&, Voltage);
Signal& operator|=(Signal&, Voltage);
Signal& operator^=(Signal&, Voltage);
Signal& operator%=(Signal&, Voltage);
//*/
}
