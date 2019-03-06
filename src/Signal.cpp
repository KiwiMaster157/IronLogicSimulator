#include "Signal.h"

//If the orange circle is filled, it means you're following my screen.
//If the orange circle is not filled, it means you're viewing independednt of me.
//The orange color just indicates what color my cursor is on your screen.

namespace iron
{

Voltage::Voltage(Level initial)
{
    level = initial;
}

Signal::Signal(int size, Voltage initial)
{
    data.resize(size, initial);
}

Signal& Signal::operator=(Signal src)
{
    std::swap(data, src.data);
    return *this;
}

int Signal::size() const
{
    return data.size();
}

Voltage& Signal::operator[](int index)
{
    return data[index];
}

const Voltage& Signal::operator[](int index) const
{
    return data[index];
}

Voltage normalize(Voltage value) noexcept
{
    switch(value.level)
    {
    case Voltage::Null:
    case Voltage::Float:
        return Voltage::Float;
    case Voltage::Low:
    case Voltage::PullLow:
        return Voltage::Low;
    case Voltage::Error:
    case Voltage::PullError:
        return Voltage::Error;
    case Voltage::High:
    case Voltage::PullHigh:
        return Voltage::High;
    }
    return Voltage::Error;
}

Signal normalize(const Signal& value)
{
    Signal retval(value.size(), Voltage::Null);
    for(int i = 0; i < value.size(); i++)
        retval[i] = normalize(value[i]);
    return retval;
}

Signal str2sig(std::string_view str)
{
    Signal retval(str.size(), Voltage::Null);

    for(int i = 0; i < str.size(); i++)
    {
        switch(str[i])
        {
        case 'N':
        case 'n':
            retval[i] = Voltage::Null;
            break;
        case 'X':
        case 'x':
        case 'F':
        case 'f':
            retval[i] = Voltage::Float;
            break;
        case '1':
            retval[i] = Voltage::High;
            break;
        case '0':
            retval[i] = Voltage::Low;
            break;
        case 'E':
        case 'R':
            retval[i] = Voltage::Error;
            break;
        case '^':
            retval[i] = Voltage::PullHigh;
            break;
        case 'v':
            retval[i] = Voltage::PullLow;
            break;
        case 'e':
        case 'r':
            retval[i] = Voltage::PullError;
            break;
        default:
            retval[i] = Voltage::Error;
        }
    }

    return retval;
}

std::string sig2str(const Signal& sig)
{
    std::string retval;
    retval.resize(sig.size());

    for(int i = 0; i < sig.size(); i++)
    {
        switch(sig[i].level)
        {
        case Voltage::Null:
            retval[i] = 'N';
            break;
        case Voltage::Float:
            retval[i] = 'x';
            break;
        case Voltage::High:
            retval[i] = '1';
            break;
        case Voltage::Low:
            retval[i] = '0';
            break;
        case Voltage::Error:
            retval[i] = 'E';
            break;
        case Voltage::PullHigh:
            retval[i] = '^';
            break;
        case Voltage::PullLow:
            retval[i] = 'v';
            break;
        case Voltage::PullError:
            retval[i] = 'e';
            break;
        default:
            retval[i] = '?';
        }
    }

    return retval;
}

//=====Comparison operators=====
bool operator==(Voltage lhs, Voltage rhs) noexcept
{
    return lhs.level == rhs.level;
}

bool operator!=(Voltage lhs, Voltage rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator==(const Signal& lhs, const Signal& rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    int length = lhs.size();

    for(int i = 0; i < length; i++)
        if(lhs[i] != rhs[i])
            return false;
    
    return true;
}

bool operator!=(const Signal& lhs, const Signal& rhs)
{
    return !(lhs == rhs);
}

//=====Implementations=====

//Valid returns: High, Low, Error
Voltage andVoltage(Voltage a, Voltage b) noexcept
{
    switch(a.level)
    {
    case Voltage::Null:
    case Voltage::Float:
        return Voltage::Error;
        break;
    case Voltage::Low:
    case Voltage::PullLow:
        return Voltage::Low;
        break;
    case Voltage::Error:
    case Voltage::PullError:
        return Voltage::Error;
        break;
    case Voltage::High:
    case Voltage::PullHigh:
        switch(b.level)
        {
        case Voltage::Null:
        case Voltage::Float:
            return Voltage::Error;
            break;
        case Voltage::Low:
        case Voltage::PullLow:
            return Voltage::Low;
            break;
        case Voltage::Error:
        case Voltage::PullError:
            return Voltage::Error;
            break;
        case Voltage::High:
        case Voltage::PullHigh:
            return Voltage::High;
        }
    }
    return Voltage();
}

//Valid returns: High, Low, Error
Voltage orVoltage(Voltage a, Voltage b) noexcept
{
    switch(a.level)
    {
    case Voltage::Null:
    case Voltage::Float:
        return Voltage::Error;
        break;
    case Voltage::Low:
    case Voltage::PullLow:
        switch(b.level)
        {
        case Voltage::Null:
        case Voltage::Float:
            return Voltage::Error;
            break;
        case Voltage::Low:
        case Voltage::PullLow:
            return Voltage::Low;
            break;
        case Voltage::Error:
        case Voltage::PullError:
            return Voltage::Error;
            break;
        case Voltage::High:
        case Voltage::PullHigh:
            return Voltage::High;
        }
        break;
    case Voltage::Error:
    case Voltage::PullError:
        return Voltage::Error;
        break;
    case Voltage::High:
    case Voltage::PullHigh:
        return Voltage::High;
    }
    return Voltage();
}

//Valid returns: High, Low, Error
Voltage xorVoltage(Voltage a, Voltage b) noexcept
{
    switch(a.level)
    {
    case Voltage::Null:
    case Voltage::Float:
        return Voltage::Error;
        break;
    case Voltage::Low:
    case Voltage::PullLow:
        switch(b.level)
        {
        case Voltage::Null:
        case Voltage::Float:
            return Voltage::Error;
            break;
        case Voltage::Low:
        case Voltage::PullLow:
            return Voltage::Low;
            break;
        case Voltage::Error:
        case Voltage::PullError:
            return Voltage::Error;
            break;
        case Voltage::High:
        case Voltage::PullHigh:
            return Voltage::High;
        }
        break;
    case Voltage::Error:
    case Voltage::PullError:
        return Voltage::Error;
        break;
    case Voltage::High:
    case Voltage::PullHigh:
        switch(b.level)
        {
        case Voltage::Null:
        case Voltage::Float:
            return Voltage::Error;
            break;
        case Voltage::Low:
        case Voltage::PullLow:
            return Voltage::High;
            break;
        case Voltage::Error:
        case Voltage::PullError:
            return Voltage::Error;
            break;
        case Voltage::High:
        case Voltage::PullHigh:
            return Voltage::Low;
        }
    }
    return Voltage();
}

//Valid returns: Any
Voltage mergeVoltage(Voltage a, Voltage b) noexcept
{
    switch(a.level)
    {
    case Voltage::Null:
        return b;
    case Voltage::Float:
        if(b == Voltage::Null)
            return Voltage::Float;
        return b;
    case Voltage::PullLow:
        switch(b.level)
        {
        case Voltage::Error:
        case Voltage::PullError:
        case Voltage::PullHigh:
            return Voltage::Error;
        case Voltage::Low:
            return Voltage::Low;
        case Voltage::High:
            return Voltage::High;
        }
        return Voltage::PullLow;
    case Voltage::PullHigh:
        switch(b.level)
        {
        case Voltage::Error:
        case Voltage::PullError:
        case Voltage::PullLow:
            return Voltage::Error;
        case Voltage::Low:
            return Voltage::Low;
        case Voltage::High:
            return Voltage::High;
        }
        return Voltage::PullHigh;
    case Voltage::PullError:
        switch(b.level)
        {
        case Voltage::Error:
        case Voltage::PullLow:
        case Voltage::PullHigh:
            return Voltage::Error;
        case Voltage::Low:
            return Voltage::Low;
        case Voltage::High:
            return Voltage::High;
        }
        return Voltage::PullError;
    case Voltage::Low:
        switch(b.level)
        {
        case Voltage::Error:
        case Voltage::High:
            return Voltage::Error;
        }
        return Voltage::Low;
    case Voltage::High:
        switch(b.level)
        {
        case Voltage::Error:
        case Voltage::Low:
            return Voltage::Error;
        }
        return Voltage::High;
    case Voltage::Error:
        return Voltage::Error;
    }
    return Voltage::Error;
}

//Valid outputs: High, Low, Error
Voltage inverseVoltage(Voltage arg) noexcept
{
    switch(arg.level)
    {
    case Voltage::Null:
    case Voltage::Float:
    case Voltage::Error:
    case Voltage::PullError:
        return Voltage::Error;
    case Voltage::Low:
    case Voltage::PullLow:
        return Voltage::High;
    case Voltage::High:
    case Voltage::PullHigh:
        return Voltage::Low;
    }
    return Voltage::Error;
}

template<Voltage fn(Voltage, Voltage)>
static Signal applySingleSignalTransform(const Signal& a, Voltage b)
{
    Signal retval;
    retval.data.resize(a.size());
    for(int i = 0; i < a.size(); i++)
    {
        retval[i] = fn(a[i], b); 
    }

    return retval;
}

template<Voltage fn(Voltage, Voltage)>
static Signal applySignalTransform(const Signal& a, const Signal& b)
{
    if(a.size() != b.size())
    {
        if(a.size() == 1)
            return applySingleSignalTransform<fn>(b, a[0]);
        if(b.size() == 1)
            return applySingleSignalTransform<fn>(a, b[0]);
        //Other possibilities: custom Voltage::Level, or throw
        return Signal(a.size(), Voltage::Error);
    }

    Signal retval;
    retval.data.resize(a.size());
    for(int i = 0; i < a.size(); i++)
    {
        retval[i] = fn(a[i], b[i]); 
    }

    return retval;
}

//======Binary Voltage Operators=====
/*
Voltage operator&(Voltage lhs, Voltage rhs)
{
    return andVoltage(lhs, rhs);
}

Voltage operator|(Voltage lhs, Voltage rhs)
{
    return orVoltage(lhs, rhs);
}

Voltage operator^(Voltage lhs, Voltage rhs)
{
    return xorVoltage(lhs, rhs);
}

Voltage operator%(Voltage lhs, Voltage rhs)
{
    return mergeVoltage(lhs, rhs);
}

Voltage& operator&=(Voltage& lhs, Voltage rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

Voltage& operator|=(Voltage& lhs, Voltage rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

Voltage& operator^=(Voltage& lhs, Voltage rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}

Voltage& operator%=(Voltage& lhs, Voltage rhs)
{
    lhs = lhs % rhs;
    return lhs;
}

//=====Signal Binary Operators=====

Signal operator&(const Signal& lhs, const Signal& rhs)
{
    return applySignalTransform<andVoltage>(lhs, rhs);
}

Signal operator|(const Signal& lhs, const Signal& rhs)
{
    return applySignalTransform<orVoltage>(lhs, rhs);
}

Signal operator^(const Signal& lhs, const Signal& rhs)
{
    return applySignalTransform<xorVoltage>(lhs, rhs);
}

Signal operator%(const Signal& lhs, const Signal& rhs)
{
    return applySignalTransform<mergeVoltage>(lhs, rhs);
}

Signal& operator&=(Signal& lhs, const Signal& rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

Signal& operator|=(Signal& lhs, const Signal& rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

Signal& operator^=(Signal& lhs, const Signal& rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}

Signal& operator%=(Signal& lhs, const Signal& rhs)
{
    lhs = lhs % rhs;
    return lhs;
}

//======Mixed Binary Opertors=====

Signal operator&(const Signal& lhs, Voltage rhs)
{
    return applySingleSignalTransform<andVoltage>(lhs, rhs);
}

Signal operator|(const Signal& lhs, Voltage rhs)
{
    return applySingleSignalTransform<orVoltage>(lhs, rhs);
}

Signal operator^(const Signal& lhs, Voltage rhs)
{
    return applySingleSignalTransform<xorVoltage>(lhs, rhs);
}

Signal operator%(const Signal& lhs, Voltage rhs)
{
    return applySingleSignalTransform<mergeVoltage>(lhs, rhs);
}

Signal& operator&=(Signal& lhs, Voltage rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

Signal& operator|=(Signal& lhs, Voltage rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

Signal& operator^=(Signal& lhs, Voltage rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}

Signal& operator%=(Signal& lhs, Voltage rhs)
{
    lhs = lhs % rhs;
    return lhs;
}
//*/

}