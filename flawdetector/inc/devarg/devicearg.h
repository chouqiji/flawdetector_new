#ifndef DEVICEARG_H
#define DEVICEARG_H

#include <QObject>

namespace DeviceArg
{

enum class CommitPolicy
{
    Immediate,
    AfterConfirmed
};

class IDeviceArgQtBase : public QObject
{
    Q_OBJECT
protected:
    IDeviceArgQtBase(QObject *parent = nullptr) : QObject{parent} {}

signals:
    void updated();
};

template <typename T>
class IDeviceArg : public IDeviceArgQtBase
{
public:
    IDeviceArg(QObject *parent = nullptr) : IDeviceArgQtBase{parent} {}
    virtual T value() const = 0;
    virtual void setValue(const T& val) = 0;
    virtual QList<T> range() const = 0;
    virtual QString argName() const = 0;
    virtual QString unit() const = 0;
    virtual void commit(CommitPolicy policy) = 0;
};

} // namespace

#endif // DEVICEARG_H
