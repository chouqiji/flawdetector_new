#include <QLabel>
#include <QBoxLayout>
#include <QKeyEvent>
#include "component/numericargeditor.h"
#include "component/utility.h"
#include <QDebug>

namespace Component {

template <typename T>
class ImplNumericArgEditor {
public:
    ImplNumericArgEditor(NumericArgEditor<T> *ptr)
        : mText{new QLabel{ptr}}, mPtr{ptr}
    {
        mText->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
        mText->setObjectName("NumericEditor");
    }

    void calcMaxLen()
    {
        mMaxLen = QString::number(mRange.second, 'f', mPrecision).size();
    }

    void initCursor()
    {
        mCursorPos = stepToCursorPos(getGlobalStep());

        while(!(mText->text().at(mapToStringPos()).isDigit()))
            mCursorPos -= 1;

        auto step = calcStep();
        if(!qFuzzyCompare(step, getGlobalStep()))
            setGlobalStep(step);

        setSelection();
    }

    void moveCursor()
    {
        mCursorPos += 1;

        qDebug()<<mCursorPos<<mMaxLen;

        if(mCursorPos == mMaxLen)
            mCursorPos = 0;
        else if(mText->text().at(mapToStringPos()) == '.')
            mCursorPos += 1;

        auto step = calcStep();
        if(!qFuzzyCompare(step, getGlobalStep()))
            setGlobalStep(step);

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
        // NOTE:如果次高位是零时，直接把step移至次高位
        if(mValue + step < -step / 10)
            step /= 10;

        mValue = std::clamp(mValue + step, mRange.first, mRange.second);

        fillText();

        // NOTE: 操作完数字后，光标一定指向有数字的位置
        while(!(mText->text().at(mapToStringPos()).isDigit()))
            mCursorPos -= 1;

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
    int mapToStringPos()
    {
        return limitDown(mMaxLen - 1 - mCursorPos, 0);
    }

    int stepToCursorPos(double step)
    {
        auto str = QString::number(step, 'f', mPrecision).rightJustified(mMaxLen, ' ');
        auto idx = str.indexOf('1');

        if(idx < 0)
            return 0;

        return mMaxLen - 1 - idx;
    }

    NumericArgEditor<T> *mPtr;
};

template<> void ImplNumericArgEditor<int>::calcMaxLen()
{
    mMaxLen = QString::number(mRange.second).length();
}

template<typename T>
NumericArgEditor<T>::NumericArgEditor(ArgPointer arg, int precision, QWidget *parent)
    : QFrame{parent}, pImpl{new ImplNumericArgEditor<T>{this}}
{
    setAttribute(Qt::WA_DeleteOnClose);
    pImpl->mArg = arg;
    pImpl->mPrecision = precision;

    grabKeyboard();

    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(pImpl->mText);

    p->setContentsMargins(0, 0, 0, 0);
    p->setSpacing(0);
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
