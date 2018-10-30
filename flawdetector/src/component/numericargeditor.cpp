#include "component/numericargeditor.h"
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>
#include <QString>
namespace Component {

NumeArgEditor::NumeArgEditor(ArgPointer arg, QWidget *parent)
    : QWidget{parent},
      mText{new QLabel{this}}

{
    setAttribute(Qt::WA_DeleteOnClose);
    mArg = arg;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);

    num_int=mArg->currentValue();
    auto range = mArg->range();
    maxLen = QString::number(range.second).length();
    mText->setText(QString::number(num_int).rightJustified(maxLen,' '));
    grabKeyboard();
    mText->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    cursor_pos=mText->text().length()-1;
    mText->setSelection(cursor_pos,1);

    p->setContentsMargins(0, 0, 0, 0);
    resize(parent->size());

}

void NumeArgEditor::bind(NumeArgEditor::ArgPointer arg)
{
    mArg = arg;

}

void NumeArgEditor::keyPressEvent(QKeyEvent *e)
{
    int modifier;
    if(e->key() == Qt::Key_Plus)
        modifier = calculateStep(cursor_pos);
    else if(e->key() == Qt::Key_Minus)
        modifier = -calculateStep(cursor_pos);
    int size_upper = mArg.data()->range().second;
    int upper_value = QString::number(size_upper).size();
    int size_lower = mArg->currentValue();
    int lower_value = QString::number(size_lower).size();
    int bit = upper_value - lower_value;
    switch(e->key())
    {
    case Qt::Key_Plus:
    case Qt::Key_Minus:
    {
        num_int=mText->text().toInt()+modifier;
        if(num_int>mArg->range().second)
            num_int=mArg->range().second;
        if(num_int<mArg->range().first)
            num_int=mArg->range().first;
        mArg->setValue(num_int);
        mText->setText(QString::number(num_int).rightJustified(maxLen,' '));
        mText->setSelection(cursor_pos,1);
        break;
    }
    case Qt::Key_Asterisk:
    {
        cursor_pos++;
        if(cursor_pos>(mText->text().size()-1))
            cursor_pos=bit;
        mText->setSelection(cursor_pos,1);
        qDebug()<<cursor_pos;
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
int NumeArgEditor::calculateStep(int cursor_step)
{
    QString max_len(maxLen, '0');
    QString update_val = max_len.replace(cursor_step,1,'1');
    int modifier_val = update_val.toInt();
    qDebug()<<modifier_val;
    return modifier_val;
}


}
