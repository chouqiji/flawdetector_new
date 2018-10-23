#ifndef IMPL_NUMERICARG_H
#define IMPL_NUMERICARG_H

#include "devicearg/numericarg.h"

namespace DeviceArg {

template <typename T>
class ConcreteNumericArg : public NumericArg<T> {
    using BasicViewPort::argChanged;
    using BasicViewPort::committed;
    using ViewPort::valueChanged;
public:
    explicit ConcreteNumericArg(NumericInitList<T> &&arg);
    ~ConcreteNumericArg() override {}

// import from editport
    virtual void setValue(const T &val) override {
        mArg.value = val;

        if(mArg.callback != nullptr)
            mArg.callback(mArg.value);

        emit committed(mArg.value);
        emit valueChanged(mArg.value);
        emit argChanged(BasicViewPort::mName + "/value", mArg.value);
    }

    virtual std::pair<T, T> range() const override {
        return mArg.range;
    }

    virtual void setRange(const std::pair<T, T>& newRange) override {
        mArg.range = newRange;
        emit argChanged(BasicViewPort::mName + "/lower_bound", newRange.first);
        emit argChanged(BasicViewPort::mName + "/upper_bound", newRange.second);
    }
    virtual CommitPolicy commitPolicy() const override {return mArg.policy;}
    virtual T currentValue() const override {return mArg.value;}

// import from viewport
    virtual QVariant value() const override {return mArg.value;}

private:
    NumericInitList<T> mArg;
};

}

#endif // IMPL_NUMERICARG_H
