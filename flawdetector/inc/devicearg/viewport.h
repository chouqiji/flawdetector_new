#ifndef DEVICEARG_VIEWPORT_H
#define DEVICEARG_VIEWPORT_H

#include <QVariant>

namespace DeviceArg {

class ViewPort : public QObject {
    Q_OBJECT
public:
    virtual QVariant value() const = 0;
    virtual QString displayedName() const = 0;
    virtual QString displayedUnit() const = 0;
    virtual ~ViewPort() = default;
signals:
    void nameChanged();
    void valueChanged();
    void unitChanged();
    void argChanged(const QString &keyType, const QVariant &value);
};

}

#endif // DEVICEARG_VIEWPORT_H
