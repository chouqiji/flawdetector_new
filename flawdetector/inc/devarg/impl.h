#ifndef DEVICEARG_IMPL_H
#define DEVICEARG_IMPL_H

#include "devarg/devicearg.h"

namespace DeviceArg
{

template <typename T>
class implDeviceArg;

template <typename T>
class ConcreteDeviceArg : public IDeviceArg<T>
{
public:
    ConcreteDeviceArg(QObject* parent = nullptr);
    ~ConcreteDeviceArg();

    virtual void setValue(const T &val);
    virtual T value() const;
    virtual QList<T> range() const;
    virtual QString argName() const;
    virtual QString unit() const;
    virtual void commit(CommitPolicy policy);

private:
    implDeviceArg<T> *pImpl;
};

template class ConcreteDeviceArg<QString>;
template class ConcreteDeviceArg<int>;
template class ConcreteDeviceArg<float>;

}

#endif // DEVICEARG_IMPL_H
