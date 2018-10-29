#ifndef ENUMERABLEARG_H
#define ENUMERABLEARG_H

#include <QSharedPointer>
#include "devicearg/basicviewport.h"
#include "devicearg/editport.h"

namespace DeviceArg {

template <typename T>
struct EnumerableInitList {
    qint32 value;
    std::pair<qint32, qint32> range;
    QList<T> list;
    CommitPolicy policy;
    std::function<void(const qint32&)> callback;
};

template <typename T>
class EnumerableArg : public BasicViewPort, public EnumerableEditPort {
public:
    virtual void setRange(const std::pair<qint32,qint32>&) = 0;
    virtual void setList(const QList<T>&) = 0;
};

template <typename T>
QSharedPointer<EnumerableArg<T>> makeArg(const QString &name, const QString &unit, EnumerableInitList<T> &&);

extern template QSharedPointer<EnumerableArg<QString>> makeArg(const QString &name, const QString &unit, EnumerableInitList<QString> &&list);

}

#endif // ENUMERABLEARG_H
