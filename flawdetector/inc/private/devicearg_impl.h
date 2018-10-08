#ifndef DEVICEARG_IMPL_H
#define DEVICEARG_IMPL_H

#include "devicearg.h"

namespace DeviceArg
{

template <typename T>
class implDeviceArg;

template <typename T>
class ConcreteDeviceArg : public IDeviceArg<T>
{
public:
    ConcreteDeviceArg(QObject* parent = nullptr);
    ConcreteDeviceArg(QObject* parent = nullptr, DeviceArgInitList<T> &&init = DeviceArgInitList<T>{});
    ~ConcreteDeviceArg();

    virtual void setValue(const T &val);
    virtual T value() const;
    virtual QList<T> range() const;
    virtual QString argName() const;
    virtual QString unit() const;
    virtual CommitPolicy commitPolicy() const;
    virtual void commit();

private:
    implDeviceArg<T> *pImpl;
};

}

#endif // DEVICEARG_IMPL_H
