#include <QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>
#include "component/enumargeditor.h"
#include "component/private/itemwheel.h"

namespace Component {

class EnumArgEditor::Impl {
public:
    Impl(EnumArgEditor *p, PopupMode mode, int wheelSize)
      : mPtr{p}
    {
        mText = new QLabel{p};
        mPopup = new ItemWheel{wheelSize, p};
        mPopupMode = mode;
    }

    void showPopup()
    {
        switch (mPopupMode) {
        case PopupMode::Absolute:
            movePopupAbs();
            break;
        case PopupMode::Relative:
            movePopupRel();
            break;
        case PopupMode::NoPopup:
            return;
        }

        mPopup->show();
    }

    Converter mConverter;
    ArgPointer mArg;
    QLabel *mText;
    ItemWheel *mPopup;
    QPoint mOffset = QPoint{0, 0};
    QPoint mPos = QPoint{0, 0};
    PopupPosRef mPopupPosRef;
    PopupMode mPopupMode = PopupMode::NoPopup;
    decltype(mArg->range()) mRange;

private:
    void movePopupRel();
    void movePopupAbs() {mPopup->move(mPos);}
    EnumArgEditor *mPtr;
};

void EnumArgEditor::Impl::movePopupRel()
{
    QPoint basePos;
    switch (mPopupPosRef) {
    case PopupPosRef::BottomLeft:
        basePos = mText->geometry().bottomLeft();
        break;
    case PopupPosRef::BottomRight:
        basePos = mText->geometry().bottomRight();
        break;
    case PopupPosRef::TopLeft:
        basePos = mText->geometry().topLeft();
        break;
    case PopupPosRef::TopRight:
        basePos = mText->geometry().topRight();
        break;
    }

    mPopup->move(mPtr->mapToGlobal(basePos) + mOffset);
}

EnumArgEditor::EnumArgEditor(ArgPointer arg, QWidget *parent, Converter converter,
                             PopupMode mode, int wheelSize)
    : QFrame{parent},
      pImpl{new Impl{this, mode, wheelSize}}
{
    setAttribute(Qt::WA_DeleteOnClose);
    pImpl->mArg = arg;
    pImpl->mConverter = converter;

    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(pImpl->mText);
    p->setContentsMargins(0, 0, 0, 0);

    connect(pImpl->mPopup, &ItemWheel::currentTextChanged, pImpl->mText, &QLabel::setText);
}

EnumArgEditor::~EnumArgEditor()
{

}

void EnumArgEditor::setPopupPosRef(PopupPosRef ref)
{
    pImpl->mPopupPosRef = ref;
}

void EnumArgEditor::setPopupRelativePos(QPoint offset)
{
    pImpl->mOffset = offset;
}

void EnumArgEditor::setPopupAbsolutePos(QPoint pos)
{
    pImpl->mPos = pos;
}

void EnumArgEditor::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Plus:
        pImpl->mPopup->selectNext();
        if(pImpl->mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            pImpl->mArg->setValue(pImpl->mPopup->currentIndex() + pImpl->mRange.first);
        break;
    case Qt::Key_Minus:
        pImpl->mPopup->selectPrev();
        if(pImpl->mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            pImpl->mArg->setValue(pImpl->mPopup->currentIndex() + pImpl->mRange.first);
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        pImpl->mArg->setValue(pImpl->mPopup->currentIndex() + pImpl->mRange.first);
        close();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

void EnumArgEditor::showEvent(QShowEvent *)
{
    pImpl->mRange = pImpl->mArg->range();
    auto lower = pImpl->mRange.first;
    const auto& list = pImpl->mArg->list();

    pImpl->mText->setFixedHeight(pImpl->mText->fontMetrics().lineSpacing());
    resize(parentWidget()->size());

    auto translated = QtConcurrent::blockingMapped(subset(list, lower, pImpl->mRange.second), pImpl->mConverter);

    pImpl->mPopup->setList(translated);
    pImpl->mPopup->setIndex(pImpl->mArg->currentValue() - lower);
    pImpl->showPopup();

    grabKeyboard();
}

}
