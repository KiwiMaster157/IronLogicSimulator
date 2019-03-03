#pragma once

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
    Voltage(Level initial);
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
Voltage normalize(Voltage value);
Signal normalize(const Signal& value);

Signal str2sig(std::string_view str);
std::string sig2str(const Signal& sig);

bool operator==(Voltage, Voltage);
bool operator!=(Voltage, Voltage);

bool operator==(const Signal&, const Signal&);
bool operator!=(const Signal&, const Signal&);

Voltage operator&(Voltage, Voltage);
Voltage operator|(Voltage, Voltage);
Voltage operator^(Voltage, Voltage);
Voltage operator%(Voltage, Voltage);

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

}
