#ifndef NUMERICARGEDITOR_H
#define NUMERICARGEDITOR_H

#include <QWidget>
#include "component/common.h"
#include "devicearg/editport.h"

class QLabel;

namespace Component {

class NumeArgEditor : public QWidget
{
    Q_OBJECT
public:
    using ArgPointer = QSharedPointer<DeviceArg::NumericEditPort<int>>;

    explicit NumeArgEditor(ArgPointer arg, QWidget *parent = nullptr);
    void bind(ArgPointer arg);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;

    ArgPointer mArg;


private:
    QLabel *mText;
    int cursor_pos;
    int num_int;
    int calculateStep(int cursor_step);
    int maxLen;
};

}


#endif // NUMERICARGEDITOR_H
