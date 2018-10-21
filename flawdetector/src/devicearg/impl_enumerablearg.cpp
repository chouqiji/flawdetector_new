#include "devicearg/private/impl_enumerablearg.h"

namespace DeviceArg {

template <typename T>
ConcreteEnumerableArg<T>::ConcreteEnumerableArg(InitList<T, ArgType::Enumerable> &&arg)
    : mArg{std::forward<decltype(mArg)>(arg)}
{
    setRange(mArg.range);
}

template<> void ConcreteEnumerableArg<QString>::setIndex(const qint32 &val)
{
    mArg.value = val;
    emit ViewPort::mSignal.valueChanged(mTranslatedRange.at(mArg.value));
    emit ViewPort::mSignal.argChanged(BasicViewPort::mName + "/value", val);
}

template<> QVariantList ConcreteEnumerableArg<QString>::range() const
{
    QVariantList ret;
    ret.reserve(mArg.range.size());
    for(const auto& e : mTranslatedRange)
        ret<<e;

    return ret;
}

template<> void ConcreteEnumerableArg<QString>::setRange(const QList<QString>& newRange)
{
    mArg.range = newRange;

    mTranslatedRange.clear();
    mTranslatedRange.reserve(newRange.size());

    for(const auto& e : newRange)
        mTranslatedRange<<QObject::tr(e.toLatin1());

    emit ViewPort::mSignal.argChanged(BasicViewPort::mName + "/range", QVariant::fromValue(newRange));

    setValue(std::clamp(mArg.value, 0, newRange.size() - 1));
}

template<> QVariant ConcreteEnumerableArg<QString>::value() const
{
    return mTranslatedRange.at(mArg.value);
}

template <typename T>
QSharedPointer<EnumerableArg<T>> makeArg(const QString &name, const QString &unit, InitList<T, ArgType::Enumerable> &&list)
{
    auto p = QSharedPointer<ConcreteEnumerableArg<T>>::create(std::forward<decltype(list)>(list));
    p->setName(name);
    p->setUnit(unit);
    return std::move(p);
}

template QSharedPointer<EnumerableArg<QString>> makeArg(const QString &name, const QString &unit, InitList<QString, ArgType::Enumerable> &&list);
} // namespace DeviceArg
