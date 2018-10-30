#include "component/numdoubleargeditor.h"
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>

namespace Component {

NumDoubleArgEditor::NumDoubleArgEditor(ArgPointer arg, QWidget *parent)
    : QWidget{parent},
      mText{new QLabel{this}}

{
    setAttribute(Qt::WA_DeleteOnClose);
    mArg = arg;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);
    num_double=mText->text().toDouble();



    num_double=mArg->currentValue();
    mText->setText(QString::number(num_double));
    grabKeyboard();
    mText->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    mText->setSelection(cursor_pos,1);

    p->setContentsMargins(0, 0, 0, 0);
    resize(parent->size());

}

void NumDoubleArgEditor::bind(NumDoubleArgEditor::ArgPointer arg)
{
    mArg = arg;

}

void NumDoubleArgEditor::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Plus:
    {
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(num_double);
        break;
    }
    case Qt::Key_Minus:
    {
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(num_double);

        break;
    }
    case Qt::Key_Asterisk:
    {
        if(cursor_pos>mText->text().size()-2)
            cursor_pos=0;
        else
            cursor_pos++;
        if(mText->text().at(cursor_pos)==QChar('.'))
            cursor_pos++;
        mText->setSelection(cursor_pos,1);

        break;
    }

    case Qt::Key_Enter:
    case Qt::Key_Return:
        releaseKeyboard();
        close();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}



}
