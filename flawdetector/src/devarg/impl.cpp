#include "private/devicearg_impl.h"

// decl of impl
template <typename T>
class DeviceArg::implDeviceArg
{
public:
    explicit implDeviceArg(ConcreteDeviceArg<T> *pParent) : mPParent{pParent}{}
    T mValue = T{};
    QList<T> mRange = QList<T>{};
    QString mArgName = QString{};
    QString mUnit = QString{};
    ~implDeviceArg() {}
private:
    ConcreteDeviceArg<T> *mPParent;
};

using namespace DeviceArg;

template class implDeviceArg<QString>;
template class implDeviceArg<int>;
template class implDeviceArg<float>;

template<typename T>
ConcreteDeviceArg<T>::ConcreteDeviceArg(QObject *parent)
    : IDeviceArg<T>{parent}, pImpl{new implDeviceArg<T>{this}}
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
    pImpl->mValue = val;
}

template<typename T>
T ConcreteDeviceArg<T>::value() const
{
    return pImpl->mValue;
}

template<typename T>
QList<T> ConcreteDeviceArg<T>::range() const
{
    return pImpl->mRange;
}

template<typename T>
QString ConcreteDeviceArg<T>::argName() const
{
    return pImpl->mArgName;
}

template<typename T>
QString ConcreteDeviceArg<T>::unit() const
{
    return pImpl->mUnit;
}

template<typename T>
void ConcreteDeviceArg<T>::commit(CommitPolicy policy)
{
    Q_UNUSED(policy);
}

QSharedPointer<IDeviceArg<int>> DeviceArg::makeIntArg(int value)
{
    auto ret = QSharedPointer<IDeviceArg<int>>{new ConcreteDeviceArg<int>{nullptr}};
    ret->setValue(value);
    return ret;
}

QSharedPointer<IDeviceArg<float>> DeviceArg::makeFloatArg(float value)
{
    auto ret = QSharedPointer<IDeviceArg<float>>{new ConcreteDeviceArg<float>{nullptr}};
    ret->setValue(value);
    return ret;
}

QSharedPointer<IDeviceArg<QString>> DeviceArg::makeQStringArg(QString value)
{
    auto ret = QSharedPointer<IDeviceArg<QString>>{new ConcreteDeviceArg<QString>{nullptr}};
    ret->setValue(value);
    return ret;
}

template<>
QSharedPointer<IDeviceArg<int>> DeviceArg::makeArg(int value)
{
    return makeIntArg(value);
}

template<>
QSharedPointer<IDeviceArg<float>> DeviceArg::makeArg(float value)
{
    return makeFloatArg(value);
}

template<>
QSharedPointer<IDeviceArg<QString>> DeviceArg::makeArg(QString value)
{
    return makeQStringArg(value);
}
