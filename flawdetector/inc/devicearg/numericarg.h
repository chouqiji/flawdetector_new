#ifndef NUMERICARG_H
#define NUMERICARG_H

#include <QSharedPointer>
#include "devicearg/basicviewport.h"
#include "devicearg/editport.h"

namespace DeviceArg {

template <typename T>
struct NumericInitList {
    T value;
    std::pair<T, T> range;
    CommitPolicy policy;
    std::function<void(const T&)> callback;
};

template <typename T>
class NumericArg : public BasicViewPort, public NumericEditPort<T> {
public:
    virtual void setRange(const std::pair<T,T>&) = 0;
};

template <typename T>
struct is_numeric {
    static constexpr bool value = std::is_integral<T>::value || std::is_floating_point<T>::value;
};

template <typename T>
typename std::enable_if<is_numeric<T>::value,
QSharedPointer<NumericArg<T>>>::type makeArg(const QString &name, const QString &unit, NumericInitList<T> &&);

extern template QSharedPointer<NumericArg<int>> makeArg<int>(const QString &name, const QString &unit, NumericInitList<int> &&list);
extern template QSharedPointer<NumericArg<double>> makeArg<double>(const QString &name, const QString &unit, NumericInitList<double> &&list);

}

#endif // NUMERICARG_H
