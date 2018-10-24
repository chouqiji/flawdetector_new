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
    constexpr int padding = 50;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(mText);
    p->setContentsMargins(0, 0, 0, 0);
    mText->setFixedHeight(mText->fontMetrics().height() + padding);
    mPopup->setWindowFlag(Qt::Popup);

    resize(parent->size());
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
        releaseKeyboard();
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

    auto translated = QtConcurrent::blockingMapped(list, mConverter);
    mPopup->setList(subset(translated, mLower, range.second));

    mPopup->setIndex(mArg->currentValue() - mLower);

    mPopup->move(mapToGlobal(mText->geometry().bottomLeft()));

    setStyleSheet(".QLabel{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:0.5 rgba(0, 0, 0, 127), stop:1 rgba(0, 0, 0, 0));}");

    mPopup->show();
    grabKeyboard();
}

void EnumArgEditor::hideEvent(QHideEvent *)
{
    releaseKeyboard();
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
