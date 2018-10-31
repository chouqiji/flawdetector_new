#include <QLabel>
#include <QBoxLayout>
#include <QKeyEvent>
#include "component/numericargeditor.h"
#include "component/utility.h"

namespace Component {

template <typename T>
class ImplNumericArgEditor {
public:
    ImplNumericArgEditor(NumericArgEditor<T> *ptr)
        : mText{new QLabel{ptr}}, mPtr{ptr}
    {
        mText->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    }

    void calcMaxLen()
    {
        mMaxLen = QString::number(mRange.second, 'f', mPrecision).size();
    }

    void initCursor()
    {
        mCursorPos = limitUp(getCursorPos(), mMaxLen - 1);

        if(!(mText->text().at(mapToStringPos()).isDigit()))
            mCursorPos += 1;

        if(mCursorPos != getCursorPos())
            setCursorPos(mCursorPos);

        setSelection();
    }

    void moveCursor()
    {
        mCursorPos += 1;

        if(mCursorPos == mMaxLen)
            mCursorPos = 0;
        else if(!(mText->text().at(mapToStringPos()).isDigit()))
            mCursorPos += 1;

        setCursorPos(mCursorPos);

        setSelection();
    }

    void fillText()
    {
        mText->setText(QString::number(mValue, 'f', mPrecision).rightJustified(mMaxLen, ' '));
    }

    void setSelection()
    {
        mText->setSelection(mapToStringPos(), 1);
    }

    T calcStep()
    {
        auto str = QString(mMaxLen, '0');
        str.replace(mapToStringPos(), 1, '1');
        if(mPrecision)
            str.replace(mMaxLen - 1 - mPrecision, 1, '.');

        return T(str.toDouble());
    }

    void addStep(T step)
    {
        mValue = std::clamp(mValue + step, mRange.first, mRange.second);
        if(mValue < step)
            ;
        fillText();
        setSelection();
    }

    typename NumericArgEditor<T>::ArgPointer mArg;
    QLabel *mText;
    int mCursorPos;
    int mMaxLen;
    int mPrecision;
    T mValue;
    std::pair<T, T> mRange;

private:
    int mapToStringPos() {
        return limitDown(mMaxLen - 1 - mCursorPos, 0);
    }
    NumericArgEditor<T> *mPtr;
};

template<> void ImplNumericArgEditor<int>::calcMaxLen()
{
    mMaxLen = QString::number(mRange.second).length();
}

template<typename T>
NumericArgEditor<T>::NumericArgEditor(ArgPointer arg, int precision, QWidget *parent)
    : QWidget{parent}, pImpl{new ImplNumericArgEditor<T>{this}}
{
    setAttribute(Qt::WA_DeleteOnClose);
    pImpl->mArg = arg;
    pImpl->mPrecision = precision;

    grabKeyboard();

    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(pImpl->mText);

    p->setContentsMargins(0, 0, 0, 0);
    resize(parent->size());

    pImpl->mValue = pImpl->mArg->currentValue();
    pImpl->mRange = pImpl->mArg->range();
    pImpl->calcMaxLen();
    pImpl->fillText();
    pImpl->initCursor();
}

template<typename T>
NumericArgEditor<T>::~NumericArgEditor()
{

}

template<typename T>
void NumericArgEditor<T>::keyPressEvent(QKeyEvent *e)
{
    T step = 0;
    if(e->key() == Qt::Key_Plus)
        step = pImpl->calcStep();
    else if(e->key() == Qt::Key_Minus)
        step = -pImpl->calcStep();

    switch (e->key())
    {
    case Qt::Key_Plus:
    case Qt::Key_Minus:
        pImpl->addStep(step);
        if(pImpl->mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            pImpl->mArg->setValue(pImpl->mValue);
        break;
    case Qt::Key_Asterisk:
        pImpl->moveCursor();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        pImpl->mArg->setValue(pImpl->mValue);
        releaseKeyboard();
        close();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

template class NumericArgEditor<int>;
template class NumericArgEditor<double>;

}
