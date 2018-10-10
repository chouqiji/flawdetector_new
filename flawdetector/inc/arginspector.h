#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QWidget>
#include "devicearg.h"

namespace Component
{

template <typename T>
class ImplArgInspector;

template <typename T>
class ArgInspector : public QWidget
{
public:
    explicit ArgInspector(QWidget* parent);
    ~ArgInspector();

    using PtrArg_t = QSharedPointer<DeviceArg::IDeviceArg<T>>;
    void bind(PtrArg_t arg);

private:
    QScopedPointer<ImplArgInspector<T>> pImpl;
    void updateValue();
};

} // namespace

#endif // ARGINSPECTOR_H
