#include "component/numericargeditor.h"
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>

namespace Component {

NumeArgEditor::NumeArgEditor(ArgPointer arg, QWidget *parent)
    : QWidget{parent},
      mText{new QLabel{this}}

{
    setAttribute(Qt::WA_DeleteOnClose);
    mArg = arg;
    constexpr int padding = 50;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);
    mText->setFixedHeight(mText->fontMetrics().height() + padding);

    num_length=mText->text().toInt();
}

void NumeArgEditor::bind(NumeArgEditor::ArgPointer arg)
{
    mArg = arg;

}

void NumeArgEditor::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Plus:
    {
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            num_length++;
            mArg->setValue(num_length);
        break;
    }
    case Qt::Key_Minus:
    {
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            num_length--;
            mArg->setValue(num_length);
        break;
    }
    case Qt::Key_Asterisk:
    {
//        if(cursor_pos>mText->text().size())
//            cursor_pos=0;
//        else
//            cursor_pos++;
//        mText->setSelection(cursor_pos,1);


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
