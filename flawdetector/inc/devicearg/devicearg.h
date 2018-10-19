#ifndef DEVICEARG_DEVICEARG_H
#define DEVICEARG_DEVICEARG_H

#include "devicearg/viewport.h"
#include "devicearg/editport.h"
#include <QSharedPointer>

namespace DeviceArg {

class BasicViewPort : public ViewPort {
public:
    virtual QString displayedName() const final { return mDisplayedName; }
    virtual QString displayedUnit() const final { return mDisplayedUnit; }
    void setUnit(const QString& unit) {
        mUnit = unit;
        mDisplayedUnit = QObject::tr(mUnit.toLatin1());
        emit mSignal.unitChanged();
        emit mSignal.argChanged(mName + "/unit", unit);
    }
    void setName(const QString& name) {
        mName = name;
        mDisplayedName = QObject::tr(mName.toLatin1());
        emit mSignal.nameChanged();
        emit mSignal.argChanged(mName + "/name", name);
    }
protected:
    QString mDisplayedName;
    QString mDisplayedUnit;
    QString mName;
    QString mUnit;
};

enum class ArgType{
    Numeric,
    Enumerable
};

template <typename T, ArgType type>
struct InitList {
    using ValueType = typename std::conditional<type == ArgType::Numeric, T, qint32>::type;
    using RangeType = typename std::conditional<type == ArgType::Numeric, std::pair<T,T>, QList<T>>::type;
    ValueType value;
    RangeType range;
    CommitPolicy policy;
    std::function<void(const ValueType&)> callback;
};

template <typename T>
class EnumerableArg : public BasicViewPort, public EnumerableEditPort {
public:
    virtual void setRange(const QList<T>&) = 0;
};

template <typename T>
class NumericArg : public BasicViewPort, public NumericEditPort<T> {
public:
    virtual void setRange(const std::pair<T,T>&) = 0;
};

template <typename T>
struct is_numeric {
    static constexpr bool value = std::is_integral<T>::value || std::is_floating_point<T>::value;
};

template <typename T>
QSharedPointer<EnumerableArg<T>> makeArg(const QString &name, const QString &unit, InitList<T, ArgType::Enumerable> &&);

template <typename T>
typename std::enable_if<is_numeric<T>::value,
QSharedPointer<NumericArg<T>>>::type makeArg(const QString &name, const QString &unit, InitList<T, ArgType::Numeric> &&);

}

#endif // DEVICEARG_DEVICEARG_H
