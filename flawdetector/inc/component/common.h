#ifndef COMMON_H
#define COMMON_H

#include <QWidget>
#include <QVariant>

namespace Component {

using Converter  = std::function<QString(const QVariant&)>;
inline QString defaultConverter(const QVariant& in) {return in.toString();}

using EditorCreator = std::function<QWidget*(QWidget*)>;

}

#endif // COMMON_H
