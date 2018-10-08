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
    virtual void commit(CommitPolicy policy) = 0;
};

QSharedPointer<IDeviceArg<int>> makeIntArg(int value);
QSharedPointer<IDeviceArg<float>> makeFloatArg(float value);
QSharedPointer<IDeviceArg<QString>> makeQStringArg(QString value);

template <typename T>
QSharedPointer<IDeviceArg<T>> makeArg(T)
{
    return QSharedPointer<IDeviceArg<T>>{}; //nullptr
}

template<> QSharedPointer<IDeviceArg<int>> makeArg(int value);
template<> QSharedPointer<IDeviceArg<float>> makeArg(float value);
template<> QSharedPointer<IDeviceArg<QString>> makeArg(QString value);

} // namespace

#endif // DEVICEARG_H
