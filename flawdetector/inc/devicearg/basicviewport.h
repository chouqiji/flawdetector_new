#ifndef DEVICEARG_DEVICEARG_H
#define DEVICEARG_DEVICEARG_H

#include "devicearg/viewport.h"
#include <QVariant>

namespace DeviceArg {

class BasicViewPort : public ViewPort {
    Q_OBJECT
public:
    virtual QString displayedName() const final { return mDisplayedName; }
    virtual QString displayedUnit() const final { return mDisplayedUnit; }
    void setUnit(const QString& unit) {
        mUnit = unit;
        mDisplayedUnit = QObject::tr(mUnit.toLatin1());
        emit unitChanged(mDisplayedUnit);
        emit argChanged(mName + "/unit", unit);
    }
    void setName(const QString& name) {
        mName = name;
        mDisplayedName = QObject::tr(mName.toLatin1());
        emit nameChanged(mDisplayedName);
        emit argChanged(mName + "/name", name);
    }
    virtual void retranslate()
    {
        mDisplayedUnit = QObject::tr(mUnit.toLatin1());
        mDisplayedName = QObject::tr(mName.toLatin1());
        emit unitChanged(mDisplayedUnit);
        emit nameChanged(mDisplayedName);
    }

protected:
    QString mDisplayedName;
    QString mDisplayedUnit;
    QString mName;
    QString mUnit;

signals:
    void argChanged(const QString &keyType, const QVariant &value);
    void committed(const QVariant &value);
};

}

#endif // DEVICEARG_DEVICEARG_H
