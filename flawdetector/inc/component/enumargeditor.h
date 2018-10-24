#ifndef COMPONENT_ARGEDITOR_H
#define COMPONENT_ARGEDITOR_H

#include <QWidget>
#include "component/common.h"
#include "devicearg/editport.h"

class QListWidget;
class QLabel;

namespace Component {

class EnumArgEditor : public QWidget
{
    Q_OBJECT
public:
    using ArgPointer = QSharedPointer<DeviceArg::EnumerableEditPort>;

    explicit EnumArgEditor(ArgPointer arg, QWidget *parent = nullptr, Converter converter = defaultConverter);
    void bind(ArgPointer arg, Converter converter = defaultConverter);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;
    virtual void moveEvent(QMoveEvent *) override;

    Converter mConverter;
    ArgPointer mArg;
    qint32 mLower;

private:
    QLabel *text;
    QListWidget *popup;
};

}

#endif // COMPONENT_ARGEDITOR_H
