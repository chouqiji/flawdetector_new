#include "private/devicearg_impl.h"

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
ConcreteDeviceArg<T>::ConcreteDeviceArg(DeviceArgInitList<T>&& init)
    : pImpl{new implDeviceArg<T>{ this,
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
    emit IDeviceArgSignals::updated();
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

template<typename T>
void ConcreteDeviceArg<T>::setRange(const QList<T> &range)
{
    pImpl->mMember.range = range;
}

template<typename T>
QString ConcreteDeviceArg<T>::argName() const
{
    return pImpl->mMember.argName;
}

template<typename T>
QString ConcreteDeviceArg<T>::unit() const
{
    return pImpl->mMember.unit;
}

template<typename T>
void ConcreteDeviceArg<T>::setUnit(const QString &unit)
{
    pImpl->mMember.unit = unit;

    emit IDeviceArgSignals::unitChanged();
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
        pImpl->mMember.callback(value());

    emit IDeviceArgSignals::committed();
}

template <typename T>
QSharedPointer<IDeviceArg<T>> DeviceArg::makeArg(struct DeviceArgInitList<T> &&value)
{
    return QSharedPointer<IDeviceArg<T> >{
        new ConcreteDeviceArg<T>{
            std::forward<DeviceArgInitList<T> >(value)
        }
    };
}

// instantiation
template class ConcreteDeviceArg<QString>;
template class ConcreteDeviceArg<int>;
template class ConcreteDeviceArg<float>;

template QSharedPointer<IDeviceArg<QString>> DeviceArg::makeArg(struct DeviceArgInitList<QString>&&);
template QSharedPointer<IDeviceArg<int>> DeviceArg::makeArg(struct DeviceArgInitList<int>&&);
template QSharedPointer<IDeviceArg<float>> DeviceArg::makeArg(struct DeviceArgInitList<float>&&);