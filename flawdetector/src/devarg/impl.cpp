#include "private/devicearg_impl.h"

template <typename T>
class DeviceArg::implDeviceArg
{
public:
    typedef DeviceArg::DeviceArgInitList<T> DataMember;

    implDeviceArg(ConcreteDeviceArg<T> *pParent) : mPParent{pParent} {}

    implDeviceArg(ConcreteDeviceArg<T> *pParent, DataMember&& member)
        : mMember{std::forward<DataMember>(member)}, mPParent{pParent} {}

    DataMember mMember;

private:
    ConcreteDeviceArg<T> *mPParent;
};

using namespace DeviceArg;

template<typename T>
ConcreteDeviceArg<T>::ConcreteDeviceArg(QObject *parent)
    : IDeviceArg<T>{parent},
      pImpl{new implDeviceArg<T>{this}}
{
}

template<typename T>
ConcreteDeviceArg<T>::ConcreteDeviceArg(QObject *parent, DeviceArgInitList<T>&& init)
    : IDeviceArg<T>{parent},
      pImpl{new implDeviceArg<T>{ this,
                                  std::forward<DeviceArgInitList<T> >(init)} }
{
}

template<typename T>
ConcreteDeviceArg<T>::~ConcreteDeviceArg()
{
    delete pImpl;
}

template<typename T>
void ConcreteDeviceArg<T>::setValue(const T &val)
{
    pImpl->mMember.value = val;
    emit updated();
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
CommitPolicy ConcreteDeviceArg<T>::commitPolicy() const
{
    return pImpl->mMember.policy;
}

template<typename T>
void ConcreteDeviceArg<T>::commit()
{
    pImpl->mMember.callback(value());
}

template <typename T>
QSharedPointer<IDeviceArg<T>> DeviceArg::makeArg(struct DeviceArgInitList<T> &&value)
{
    return QSharedPointer<IDeviceArg<T>>
           { new ConcreteDeviceArg<T>
                 { nullptr,
                   std::forward<DeviceArgInitList<T> >(value)}
           };
}

// instantiation
template class ConcreteDeviceArg<QString>;
template class ConcreteDeviceArg<int>;
template class ConcreteDeviceArg<float>;

template class implDeviceArg<QString>;
template class implDeviceArg<int>;
template class implDeviceArg<float>;

template QSharedPointer<IDeviceArg<QString>> DeviceArg::makeArg(struct DeviceArgInitList<QString>&&);
template QSharedPointer<IDeviceArg<int>> DeviceArg::makeArg(struct DeviceArgInitList<int>&&);
template QSharedPointer<IDeviceArg<float>> DeviceArg::makeArg(struct DeviceArgInitList<float>&&);
