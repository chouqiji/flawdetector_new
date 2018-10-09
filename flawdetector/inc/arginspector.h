#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QWidget>
#include "devicearg.h"

class ImplArgInspector;

class ArgInspector : public QWidget
{
    Q_OBJECT

public:
    explicit ArgInspector(QWidget* parent);
    ~ArgInspector();

    using PtrStrArg_t = QSharedPointer<DeviceArg::IDeviceArg<QString>>;

    void bind(PtrStrArg_t arg);

private:
    QScopedPointer<ImplArgInspector> pImpl;
};

#endif // ARGINSPECTOR_H