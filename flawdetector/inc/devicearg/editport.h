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
    virtual ~EditPort() = default;
};

class EnumerableEditPort : public EditPort {
public:
    virtual void setValue(const qint32 &val) { setIndex(std::forward<const qint32 &>(val));}
    virtual void setIndex(const qint32 &) = 0;
    virtual std::pair<qint32, qint32> range() const = 0;
    virtual QVariantList list() const = 0;
    virtual qint32 currentValue() const { return index();}
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
