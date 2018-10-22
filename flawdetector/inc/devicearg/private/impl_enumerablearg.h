#ifndef DEVICEARG_IMPL_ENUMERABLEARG_H
#define DEVICEARG_IMPL_ENUMERABLEARG_H

#include "devicearg/enumerablearg.h"
#include <utility>

namespace DeviceArg {

template <typename T>
class ConcreteEnumerableArg : public EnumerableArg<T>
{
    using BasicViewPort::argChanged;
    using BasicViewPort::committed;
    using ViewPort::valueChanged;
public:
    ConcreteEnumerableArg(EnumerableInitList<T> &&arg);
    ~ConcreteEnumerableArg() override {}

// import from editport
    virtual void setIndex(const qint32 &val) override {
        mShadowValue = val;
    }

    virtual std::pair<qint32, qint32> range() const override {
        return mArg.range;
    }

    virtual void setRange(const std::pair<qint32, qint32>& newRange) override {
        mArg.range = newRange;
        emit argChanged(BasicViewPort::mName + "/lower_bound", newRange.first);
        emit argChanged(BasicViewPort::mName + "/upper_bound", newRange.second);
    }

    virtual QVariantList list() const override {
        QVariantList ret;
        ret.reserve(mArg.range.size());
        for(const auto& e : mArg.range)
            ret<<e;
        return ret;
    }

    virtual void setList(const QList<T>& newList) override {
        mArg.list = newList;
        emit argChanged(BasicViewPort::mName + "/list", QVariant::fromValue(newList));

        translateList(newList);

        mArg.range.second = newList.size() - 1;

        if(mArg.value != std::clamp(mArg.value, mArg.range.first, mArg.range.second))
        {
            setIndex(mArg.value);
            commit();
        }
    }

    virtual qint32 index() const override {return mArg.value;}
    virtual CommitPolicy commitPolicy() const override {return mArg.policy;}
    virtual void commit() override {

        mArg.value = mShadowValue;

        if(mArg.callback != nullptr)
            mArg.callback(mArg.value);

        emit committed(mArg.value);
        emit valueChanged(translateValue(mArg.value));
        emit argChanged(BasicViewPort::mName + "/value", mArg.value);
    }

// import from viewport
    virtual QVariant value() const override {return translateValue(mArg.value);}

private:
    EnumerableInitList<T> mArg;
    QStringList mTranslatedList;
    qint32 mShadowValue;

    void translateList(const QList<T>&) {}
    QVariant translateValue(const qint32& value) const { return mArg.list.at(value);}
};

}

#endif // DEVICEARG_IMPL_ENUMERABLEARG_H
