#ifndef COMMON_H
#define COMMON_H

#include <QWidget>
#include <QVariant>

namespace Component {

using Converter  = std::function<QString(const QVariant&)>;
inline QString defaultConverter(const QVariant& in) {return in.toString();}

using EditorCreator = std::function<QWidget*(QWidget*)>;

template <typename T>
inline T subset(const T& in, int lower, int upper)
{
    T ret;
    for(int i = lower; i <= upper; ++i)
        ret<<in[i];

    return std::move(ret);
}

}

#endif // COMMON_H
