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
    IDeviceArgSignals(QObject *parent = nullptr) : QObject{parent} {}
    IDeviceArgSignals(const IDeviceArgSignals&) = default;
    ~IDeviceArgSignals() = default;
    IDeviceArgSignals& operator=(const IDeviceArgSignals&) = default;

signals:
    void unitChanged();
    void valueChanged();
    void committed();
    void settingChanged(const QString &key, const QVariant &value);
};

template <typename T>
class IDeviceArg : public IDeviceArgSignals
{
protected:
    IDeviceArg(QObject *parent = nullptr) : IDeviceArgSignals{parent} {}

public:
    virtual QString argName() const = 0;
    virtual T value() const = 0;
    virtual void setValue(const T&) = 0;
    virtual QList<T> range() const = 0;
    virtual void setRange(const QList<T>&) = 0;
    virtual QString unit() const = 0;
    virtual void setUnit(const QString&) = 0;
    virtual CommitPolicy commitPolicy() const = 0;
    // slot
    virtual void commit() = 0;
};

template <typename T>
struct DeviceArgInitList
{
    QString argToken;
    QString argName;
    T value;
    QList<T> range;
    QString unit;
    CommitPolicy policy;
    std::function<void(const T&)> callback;
};

template <typename T>
QSharedPointer<IDeviceArgSignals> makeArg(struct DeviceArgInitList<T>&&, QObject *parent = nullptr);

} // namespace

#endif // DEVICEARG_H
