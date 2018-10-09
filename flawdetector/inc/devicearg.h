#ifndef DEVICEARG_H
#define DEVICEARG_H

#include <QObject>
#include <QSharedPointer>
#include <functional>

namespace DeviceArg
{

enum class CommitPolicy
{
    Immediate,
    AfterConfirmed
};

class IDeviceArgSignals : public QObject
{
    Q_OBJECT
protected:
    IDeviceArgSignals() = default;
    IDeviceArgSignals(const IDeviceArgSignals&) = default;
    ~IDeviceArgSignals() = default;
    IDeviceArgSignals& operator=(const IDeviceArgSignals&) = default;

signals:
    void unitChanged();
    void updated();
    void committed();
};

template <typename T>
class IDeviceArg : public IDeviceArgSignals
{
public:
    virtual T value() const = 0;
    virtual void setValue(const T&) = 0;
    virtual QList<T> range() const = 0;
    virtual void setRange(const QList<T>&) = 0;
    virtual QString argName() const = 0;
    virtual QString unit() const = 0;
    virtual void setUnit(const QString&) = 0;
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
    std::function<void(const T&)> callback;
};

template <typename T>
QSharedPointer<IDeviceArg<T>> makeArg(struct DeviceArgInitList<T>&&);

} // namespace

#endif // DEVICEARG_H
