#ifndef COMPONENT_ARGEDITOR_H
#define COMPONENT_ARGEDITOR_H

#include <QComboBox>
#include "component/common.h"
#include "devicearg/editport.h"

namespace Component {

class EnumArgEditor : public QComboBox
{
    Q_OBJECT
public:
    explicit EnumArgEditor(QWidget *parent = nullptr);

    using ArgPointer = QSharedPointer<DeviceArg::EnumerableEditPort>;

    void bind(ArgPointer arg, Converter converter = defaultConverter);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void showEvent(QShowEvent *) override;

    Converter mConverter;
    ArgPointer mArg;
    qint32 mLower;
};

}

#endif // COMPONENT_ARGEDITOR_H
