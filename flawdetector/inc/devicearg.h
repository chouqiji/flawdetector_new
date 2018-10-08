#ifndef DEVICEARG_H
#define DEVICEARG_H

#include <QObject>
#include <QSharedPointer>

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
    virtual CommitPolicy commitPolicy() const = 0;
    // slot
    virtual void commit() = 0;
};

template <typename T>
struct DeviceArgInitList
{
    QString argName;
    T value;
    QList<T> range;
    QString unit;
    CommitPolicy policy;
};

template <typename T>
QSharedPointer<IDeviceArg<T>> makeArg(struct DeviceArgInitList<T>&&);

} // namespace

#endif // DEVICEARG_H
