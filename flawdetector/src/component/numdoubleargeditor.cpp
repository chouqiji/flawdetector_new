#include "component/numdoubleargeditor.h"
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>
#include <QDebug>
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
    auto range = mArg->range();
    maxLen = QString::number(range.second).length();
    mText->setText(QString::number(num_double,'f',1).rightJustified(maxLen,' '));

    grabKeyboard();
    mText->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    cursor_pos=mText->text().length()-1;
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
    int modifier;
    if(e->key() == Qt::Key_Plus)
        modifier = calculateStep(cursor_pos);
    else if(e->key() == Qt::Key_Minus)
        modifier = -calculateStep(cursor_pos);
    double size_upper = mArg.data()->range().second;
    int upper_value = QString::number(size_upper).size();
    double size_lower = mArg->currentValue();
    int lower_value = QString::number(size_lower).size();
    int bit = upper_value - lower_value;


    switch(e->key())
    {
    case Qt::Key_Plus:
    case Qt::Key_Minus:
    {
        num_double=mText->text().toDouble()+modifier;

        if(num_double>mArg->range().second)
            num_double=mArg->range().second;
        if(num_double<mArg->range().first)
            num_double=mArg->range().first;
        mArg->setValue(num_double);
        mText->setText(QString::number(num_double,'f',1).rightJustified(maxLen,' '));
        mText->setSelection(cursor_pos,1);
        break;
    }

    case Qt::Key_Asterisk:
    {
        cursor_pos++;
        if(cursor_pos>mText->text().size()-1)
            cursor_pos=bit;
        if(mText->text().at(cursor_pos)==QChar('.'))
        {
            cursor_pos++;
            qDebug()<<cursor_pos;
        }
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

int NumDoubleArgEditor::calculateStep(int cursor_step)
{
//    QString max_len(maxLen, '0');
//    QString update_val = max_len.replace(cursor_step,1,'1');

//    double modifier_val = update_val.toDouble();

//    return modifier_val;

}

}
