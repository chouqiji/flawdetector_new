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
public slots:
    virtual void commit(CommitPolicy policy) = 0;

signals:
    void updated();
};

template <typename T>
class IDeviceArg : public IDeviceArgQtBase
{
public:
    virtual T getValue() = 0;
    // for number types, getRange() returns a list of size 2
    // for string types, getRange() should return list of strings
    virtual QList<T> getRange() = 0;
    virtual QString getArgName() = 0;
    virtual QString getUnit() = 0;
};

} // namespace
class implDeviceArg;

template <typename T>
class DeviceArg : public IDeviceArgs<T>
{
public:
    DeviceArg(QObject* parent);
private:
    QScopedPointer<implDeviceArg> pImpl;
};

using DeviceArgsString = DeviceArg<QString>;

#endif // DEVICEARG_H
