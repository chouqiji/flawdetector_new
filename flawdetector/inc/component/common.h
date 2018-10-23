#ifndef COMMON_H
#define COMMON_H

#include <QVariant>

namespace Component {

using Converter  = std::function<QString(const QVariant&)>;
inline QString defaultConverter(const QVariant& in) {return in.toString();}

}

#endif // COMMON_H
