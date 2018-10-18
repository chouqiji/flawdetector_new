#ifndef DEVICEARG_EDITPORT_H
#define DEVICEARG_EDITPORT_H

#include <QVariant>

namespace DeviceArg {

enum class CommitPolicy
{
    Immediate,
    AfterConfirmed
};

class EditPort {
public:
    virtual CommitPolicy commitPolicy() const = 0;
    virtual void commit() = 0;
    virtual ~EditPort();
};

class EnumerableEditPort : public EditPort {
public:
    virtual void setIndex(const qint32 &) = 0;
    virtual QVariantList range() const = 0;
    virtual qint32 index() const = 0;
};

template <typename T>
class NumericEditPort : public EditPort {
public:
    virtual void setValue(const T &) = 0;
    virtual std::pair<T, T> range() const = 0;
    virtual T currentValue() const = 0;
};

}

#endif // DEVICEARG_EDITPORT_H
