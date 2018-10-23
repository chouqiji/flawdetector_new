#include "component/enumargeditor.h"
#include <QKeyEvent>

namespace Component {

EnumArgEditor::EnumArgEditor(QWidget *parent) : QComboBox(parent)
{
    hide();
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
        auto idx = currentIndex() + 1 == count() ? currentIndex() : currentIndex() + 1;
        setCurrentIndex(idx);
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(currentIndex() + mLower);
        break;
    }
    case Qt::Key_Minus:
    {
        auto idx = currentIndex() - 1 < 0 ? 0 : currentIndex() - 1;
        setCurrentIndex(idx);
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(currentIndex() + mLower);
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
        mArg->setValue(currentIndex() + mLower);
        releaseKeyboard();
        hide();
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
    clear();
    for(int i = mLower; i <= range.second; ++i)
    {
        addItem(mConverter(list[i]));
    }
    setCurrentIndex(mArg->currentValue() - mLower);
    grabKeyboard();
}

}
