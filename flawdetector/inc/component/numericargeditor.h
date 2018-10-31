#ifndef COMPONENT_NUMERICARGEDITOR_H
#define COMPONENT_NUMERICARGEDITOR_H

#include <QFrame>
#include <devicearg/editport.h>

namespace Component {

template <typename T>
class ImplNumericArgEditor;

template <typename T>
class NumericArgEditor : public QFrame
{
public:
    using ArgPointer = QSharedPointer<DeviceArg::NumericEditPort<T>>;
    explicit NumericArgEditor(ArgPointer arg, int precision = 0, QWidget *parent = nullptr);
    ~NumericArgEditor();

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;

private:
    QScopedPointer<ImplNumericArgEditor<T>> pImpl;
};

}

#endif // COMPONENT_NUMERICARGEDITOR_H
