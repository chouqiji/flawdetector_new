#ifndef DEVICEARG_DEVICEARG_H
#define DEVICEARG_DEVICEARG_H

#include "devicearg/viewport.h"
#include "devicearg/editport.h"

namespace DeviceArg {

class EnumerableArg : public ViewPort, public EnumerableEditPort{
};

template <typename T>
class NumericArg : public ViewPort, public NumericEditPort<T>{
};

template <typename T>
QSharedPointer<EnumerableArg> makeArg();

}

#endif // DEVICEARG_DEVICEARG_H
