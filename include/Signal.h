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

constexpr int SIGNAL_STACK_CAPACITY = (sizeof(void*) + sizeof(int)) / sizeof(Voltage);
    
class Signal
{
    int m_size = 0;
    union
    {
        struct{int capacity, Voltage* ptr;} heap;
        Voltage stack[SIGNAL_STACK_CAPACITY];
    } m_data;
public:  
    Signal();
    Signal(const Signal&);
    Signal(Signal&&);
    
    ~Signal();

    Signal& operator=(const Signal& src);
    Signal& operator=(Signal&& src);
    
    Signal(int size, Voltage initial);

    int size() const;
    void resize(int newSize);

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
