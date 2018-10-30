#ifndef COMPONENT_ARGEDITOR_H
#define COMPONENT_ARGEDITOR_H

#include <QFrame>
#include "component/common.h"
#include "devicearg/editport.h"


class QListWidget;
class QLabel;

namespace Component {

class ItemWheel;

enum class PopupPosRef{
    BottomLeft, BottomRight, TopLeft, TopRight
};

enum class PopupMode{
    Relative, Absolute, NoPopup
};

class EnumArgEditor : public QFrame
{
    Q_OBJECT
public:
    using ArgPointer = QSharedPointer<DeviceArg::EnumerableEditPort>;

    explicit EnumArgEditor(ArgPointer arg, QWidget *parent = nullptr,
                           Converter converter = defaultConverter,
                           PopupMode mode = PopupMode::NoPopup,
                           int wheelSize = 5);
    ~EnumArgEditor() override;

    void setPopupPosRef(PopupPosRef ref);
    void setPopupRelativePos(QPoint offset);
    void setPopupAbsolutePos(QPoint pos);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void showEvent(QShowEvent *) override;

private:
    class Impl;
    QScopedPointer<Impl> pImpl;
};

}

#endif // COMPONENT_ARGEDITOR_H
