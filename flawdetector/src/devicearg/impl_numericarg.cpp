#include "devicearg/private/impl_numericarg.h"

namespace DeviceArg {

template<typename T>
ConcreteNumericArg<T>::ConcreteNumericArg(NumericInitList<T> &&arg)
    : mArg{std::forward<decltype(mArg)>(arg)}
{
}

template <typename T>
typename std::enable_if<is_numeric<T>::value,
QSharedPointer<NumericArg<T>>>::type makeArg(const QString &name, const QString &unit, NumericInitList<T> &&list)
{
    auto p = QSharedPointer<ConcreteNumericArg<T>>::create(std::forward<decltype(list)>(list));
    p->setName(name);
    p->setUnit(unit);

    return std::move(p);
}

template QSharedPointer<NumericArg<int>> makeArg<int>(const QString &name, const QString &unit, NumericInitList<int> &&list);
template QSharedPointer<NumericArg<double>> makeArg<double>(const QString &name, const QString &unit, NumericInitList<double> &&list);

}
