#ifndef NUMDOUBLEARGEDITOR_H
#define NUMDOUBLEARGEDITOR_H

#include <QWidget>
#include "component/common.h"
#include "devicearg/editport.h"

class QLabel;

namespace Component {

class NumDoubleArgEditor : public QWidget
{
    Q_OBJECT
public:
    using ArgPointer = QSharedPointer<DeviceArg::NumericEditPort<double>>;

    explicit NumDoubleArgEditor(ArgPointer arg, QWidget *parent = nullptr);
    void bind(ArgPointer arg);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;

    ArgPointer mArg;


private:
    QLabel *mText;
    double num_double;
    int cursor_pos=0;
    QString num;
    double num_todouble;
    int calculateStep(int cursor_step);
    int maxLen;
};

}



#endif // NUMDOUBLEARGEDITOR_H
