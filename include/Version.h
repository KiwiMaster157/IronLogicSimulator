#pragma once

#include <string>

namespace iron {

struct Version
{
    short major = 0;
    short minor = 0;
    short build = 0;
    short rev = 0;
};
}

namespace std
{

inline string to_string(const ::iron::Version& vers)
{
    return to_string(vers.major) + "."
        + to_string(vers.minor) + "."
        + to_string(vers.build) + ":"
        + to_string(vers.rev);
}

}