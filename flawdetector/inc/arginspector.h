#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QWidget>
#include "devicearg/viewport.h"

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

    using PtrArg = QSharedPointer<DeviceArg::ViewPort>;
    void bind(PtrArg arg);

private:
    QScopedPointer<ImplArgInspector<T>> pImpl;
private slots:
    void updateValue();
};

} // namespace

#endif // ARGINSPECTOR_H
