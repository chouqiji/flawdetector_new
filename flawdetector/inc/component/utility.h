#ifndef UTILITY_H
#define UTILITY_H

#include <utility>

namespace Component {

template <typename T>
inline T subset(const T& in, int lower, int upper)
{
    T ret;
    for(int i = lower; i <= upper; ++i)
        ret<<in[i];

    return std::move(ret);
}

template <typename T>
inline T limitUp(const T& in, const T& upper)
{
    return in > upper ? upper : in;
}

template <typename T>
inline T limitDown(const T& in, const T& lower)
{
    return in < lower ? lower : in;
}

extern int getCursorPos();
extern void setCursorPos(int);

}

#endif // UTILITY_H
