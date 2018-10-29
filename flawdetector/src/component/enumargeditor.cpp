#include "component/enumargeditor.h"
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>

namespace Component {

EnumArgEditor::EnumArgEditor(ArgPointer arg, QWidget *parent, Converter converter)
    : QWidget{parent},
      mText{new QLabel{this}},
      mPopup{new ItemWheel{5, this}}
{
    setAttribute(Qt::WA_DeleteOnClose);
    mArg = arg;
    mConverter = converter;

    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);
    p->setContentsMargins(0, 0, 0, 0);
    mText->setFixedHeight(mText->fontMetrics().lineSpacing());

    connect(mPopup, &ItemWheel::currentTextChanged, mText, &QLabel::setText);
}

void EnumArgEditor::bind(EnumArgEditor::ArgPointer arg, Converter converter)
{
    mArg = arg;
    mConverter = converter;
}

void EnumArgEditor::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Plus:
    {
        mPopup->selectNext();
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(mPopup->currentIndex() + mLower);

        break;
    }
    case Qt::Key_Minus:
    {
        mPopup->selectPrev();
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(mPopup->currentIndex() + mLower);

        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
        mArg->setValue(mPopup->currentIndex() + mLower);
        close();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

void EnumArgEditor::showEvent(QShowEvent *)
{
    auto range = mArg->range();
    mLower = range.first;
    const auto& list = mArg->list();

    resize(parentWidget()->size());

    auto translated = QtConcurrent::blockingMapped(list, mConverter);
    mPopup->setList(subset(translated, mLower, range.second));

    mPopup->setIndex(mArg->currentValue() - mLower);

    mPopup->move(mapToGlobal(mText->geometry().bottomLeft()));

    mPopup->show();
    grabKeyboard();
}

void EnumArgEditor::hideEvent(QHideEvent *)
{
    releaseKeyboard();
    mPopup->hide();
}

void EnumArgEditor::resizeEvent(QResizeEvent *)
{
    mPopup->setFixedWidth(mText->geometry().width());
}

void EnumArgEditor::moveEvent(QMoveEvent *)
{
    mPopup->move(mapToGlobal(mText->geometry().bottomLeft()));
}

}
