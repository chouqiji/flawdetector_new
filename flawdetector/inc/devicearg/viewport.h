#ifndef DEVICEARG_VIEWPORT_H
#define DEVICEARG_VIEWPORT_H

#include <QObject>

namespace DeviceArg {

class ViewPort : public QObject{
    Q_OBJECT
public:
    virtual QVariant value() const = 0;
    virtual QString displayedName() const = 0;
    virtual QString displayedUnit() const = 0;
    virtual ~ViewPort() = default;

signals:
    void nameChanged(const QString&);
    void valueChanged(const QVariant&);
    void unitChanged(const QString&);
};

}

#endif // DEVICEARG_VIEWPORT_H
