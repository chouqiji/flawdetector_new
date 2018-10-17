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

enum class ArgType
{
    Numeric,
    Enumerable
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
    void valueChanged();
    void unitChanged();
    void committed(); // call route:
    void settingChanged(const QString &key, const QVariant &value);
};

template <typename T>
struct is_numeric
{
    static constexpr bool value = std::is_integral<T>::value || std::is_floating_point<T>::value;
};

template <typename T>
struct NumericRange
{
    T lower;
    T upper;
};

template <typename T, ArgType type = ArgType::Numeric>
class IDeviceArg : public IDeviceArgSignals
{
protected:
    IDeviceArg(QObject *parent = nullptr) : IDeviceArgSignals{parent} {}

public:
    using ValueType = typename std::conditional
                    <type == ArgType::Numeric && is_numeric<T>::value
                    , T, qint32>::type;

    using RangeType = typename std::conditional
                    <type == ArgType::Numeric && is_numeric<T>::value
                    , NumericRange<T>, QList<T>>::type;

    virtual QString argName() const = 0;
    virtual ValueType value() const = 0;
    virtual void setValue(const ValueType&) = 0;
    virtual RangeType range() const = 0;
    virtual void setRange(const RangeType&) = 0;
    virtual QString unit() const = 0;
    virtual void setUnit(const QString&) = 0;
    virtual CommitPolicy commitPolicy() const = 0;
    // slot
    virtual void commit() = 0;
};

template <typename T, ArgType type = ArgType::Numeric>
struct DeviceArgInitList
{
    using ValueType = typename IDeviceArg<T, type>::ValueType;
    using RangeType = typename IDeviceArg<T, type>::RangeType;
    QString argName;
    ValueType value;
    QString unit;
    RangeType range;
    CommitPolicy policy;
    std::function<void(const ValueType&)> callback;
};

template <typename T>
QSharedPointer<IDeviceArgSignals> makeNumericArg(struct DeviceArgInitList<T>&&, QObject *parent = nullptr);

template <typename T>
QSharedPointer<IDeviceArgSignals> makeEnumerableArg(struct DeviceArgInitList<T>&&, QObject *parent = nullptr);

} // namespace

#endif // DEVICEARG_H
