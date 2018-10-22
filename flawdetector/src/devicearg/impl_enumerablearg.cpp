#include "devicearg/private/impl_enumerablearg.h"

namespace DeviceArg {

template <typename T>
ConcreteEnumerableArg<T>::ConcreteEnumerableArg(EnumerableInitList<T> &&arg)
    : mArg{std::forward<decltype(mArg)>(arg)}
{
    translateList(mArg.list);
}

template<> void ConcreteEnumerableArg<QString>::translateList(const QList<QString>& newList)
{
    mTranslatedList.clear();
    mTranslatedList.reserve(newList.size());

    for(const auto& e : newList)
        mTranslatedList<<QObject::tr(e.toLatin1());
}

template<> QVariant ConcreteEnumerableArg<QString>::translateValue(const qint32& value) const
{
    return mTranslatedList.at(value);
}

template<> QVariantList ConcreteEnumerableArg<QString>::list() const
{
    QVariantList ret;
    ret.reserve(mTranslatedList.size());
    for(const auto& e : mTranslatedList)
        ret<<e;

    return ret;
}

template <typename T>
QSharedPointer<EnumerableArg<T>> makeArg(const QString &name, const QString &unit, EnumerableInitList<T> &&list)
{
    auto p = QSharedPointer<ConcreteEnumerableArg<T>>::create(std::forward<decltype(list)>(list));
    p->setName(name);
    p->setUnit(unit);
    return std::move(p);
}

template QSharedPointer<EnumerableArg<QString>> makeArg(const QString &name, const QString &unit, EnumerableInitList<QString> &&list);
} // namespace DeviceArg
