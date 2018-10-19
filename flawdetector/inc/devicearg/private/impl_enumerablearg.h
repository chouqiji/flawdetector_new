#ifndef DEVICEARG_IMPL_ENUMERABLEARG_H
#define DEVICEARG_IMPL_ENUMERABLEARG_H

#include "devicearg/devicearg.h"

namespace DeviceArg {

template <typename T>
class ConcreteEnumerableArg : public EnumerableArg<T>
{
public:
    ConcreteEnumerableArg(InitList<T, ArgType::Enumerable> &&arg);
    ~ConcreteEnumerableArg() {}

// import from editport
    virtual void setIndex(const qint32 &val) override {
        mArg.value = val;
        emit ViewPort::mSignal.valueChanged();
        emit ViewPort::mSignal.argChanged(BasicViewPort::mName + "/value", val);
    }
    virtual QVariantList range() const override {
        QVariantList ret;
        ret.reserve(mArg.range.size());
        for(const auto& e : mArg.range)
            ret<<e;
        return ret;
    }
    virtual void setRange(const QList<T>& newRange) override {
        mArg.range = newRange;
        emit ViewPort::mSignal.argChanged(BasicViewPort::mName + "/range", QVariant::fromValue(newRange));

        setValue(std::clamp(mArg.value, 0, newRange.size() - 1));
    }
    virtual qint32 index() const override {return mArg.value;}
    virtual CommitPolicy commitPolicy() const override {return mArg.policy;}
    virtual void commit() override {
        if(mArg.callback != nullptr)
            mArg.callback(mArg.value);

        emit ViewPort::mSignal.committed(mArg.value);
    }

// import from viewport
    virtual QVariant value() const override {return mArg.value;}

private:
    InitList<T, ArgType::Enumerable> mArg;
    QStringList mTranslatedRange;
};

}

#endif // DEVICEARG_IMPL_ENUMERABLEARG_H
