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
    constexpr int padding = 50;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);
    mText->setFixedHeight(mText->fontMetrics().height() + padding);

    num_double=mText->text().toDouble();
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
        if(cursor_pos>mText->text().size())
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
