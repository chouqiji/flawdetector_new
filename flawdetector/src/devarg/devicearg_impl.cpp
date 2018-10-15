#include "private/devicearg_impl.h"
#include <QVariant>

template <typename T>
class DeviceArg::implDeviceArg
{
public:
    typedef DeviceArg::DeviceArgInitList<T> DataMember;

    implDeviceArg(ConcreteDeviceArg<T> *pParent) : mPtrParent{pParent} {}

    implDeviceArg(ConcreteDeviceArg<T> *pParent, DataMember&& member)
        : mMember{std::forward<DataMember>(member)}, mPtrParent{pParent} {}

    DataMember mMember;

private:
    ConcreteDeviceArg<T> *mPtrParent;
};

using namespace DeviceArg;

template<typename T>
ConcreteDeviceArg<T>::ConcreteDeviceArg(DeviceArgInitList<T>&& init, QObject *parent)
    : IDeviceArg<T>{parent},
      pImpl{new implDeviceArg<T>{ this,
                                  std::forward<DeviceArgInitList<T> >(init)} }
{
}

template<typename T>
ConcreteDeviceArg<T>::~ConcreteDeviceArg()
{
}

template<typename T>
void ConcreteDeviceArg<T>::setValue(const T &val)
{
    pImpl->mMember.value = val;
    emit IDeviceArgSignals::valueChanged();
    emit IDeviceArgSignals::settingChanged(pImpl->mMember.argToken+"/value", val);
}

template<typename T>
T ConcreteDeviceArg<T>::value() const
{
    return pImpl->mMember.value;
}

template<typename T>
QList<T> ConcreteDeviceArg<T>::range() const
{
    return pImpl->mMember.range;
}

namespace DeviceArg {
template<>
QString ConcreteDeviceArg<QString>::value() const
{
    return QObject::tr(pImpl->mMember.value.toLatin1());
}

template<>
QList<QString> ConcreteDeviceArg<QString>::range() const
{
    QList<QString> list;
    for(const auto& str : pImpl->mMember.range)
        list<<QObject::tr(str.toLatin1());

    return list;
}
}

template<typename T>
void ConcreteDeviceArg<T>::setRange(const QList<T> &range)
{
    pImpl->mMember.range = range;

    emit IDeviceArgSignals::settingChanged(pImpl->mMember.argToken+"/range", QVariant::fromValue(range));
}

template<typename T>
QString ConcreteDeviceArg<T>::argName() const
{
    return QObject::tr(pImpl->mMember.argName.toLatin1());
}

template<typename T>
QString ConcreteDeviceArg<T>::unit() const
{
    return QObject::tr(pImpl->mMember.unit.toLatin1());
}

template<typename T>
void ConcreteDeviceArg<T>::setUnit(const QString &unit)
{
    pImpl->mMember.unit = unit;

    emit IDeviceArgSignals::unitChanged();
    emit IDeviceArgSignals::settingChanged(pImpl->mMember.argToken+"/unit", unit);
}

template<typename T>
CommitPolicy ConcreteDeviceArg<T>::commitPolicy() const
{
    return pImpl->mMember.policy;
}

template<typename T>
void ConcreteDeviceArg<T>::commit()
{
    if(pImpl->mMember.callback != nullptr)
        pImpl->mMember.callback(value()); // synchronized

    emit IDeviceArgSignals::committed(); // can be asynchronized
}

template <typename T>
QSharedPointer<IDeviceArgSignals> DeviceArg::makeArg(struct DeviceArgInitList<T> &&value, QObject *parent)
{
    return QSharedPointer<IDeviceArgSignals>{
        new ConcreteDeviceArg<T>{
            std::forward<DeviceArgInitList<T> >(value), parent
        }
    };
}

// instantiation
template class ConcreteDeviceArg<QString>;
template class ConcreteDeviceArg<int>;
template class ConcreteDeviceArg<float>;

template QSharedPointer<IDeviceArgSignals> DeviceArg::makeArg(struct DeviceArgInitList<QString>&&, QObject *parent);
template QSharedPointer<IDeviceArgSignals> DeviceArg::makeArg(struct DeviceArgInitList<int>&&, QObject *parent);
template QSharedPointer<IDeviceArgSignals> DeviceArg::makeArg(struct DeviceArgInitList<float>&&, QObject *parent);
