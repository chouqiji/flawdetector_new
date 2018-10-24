#include "component/enumargeditor.h"
#include <QComboBox>
#include <QKeyEvent>
#include <QListWidget>
#include <QtConcurrent/QtConcurrentMap>
#include <QLabel>
#include <QBoxLayout>

namespace Component {

EnumArgEditor::EnumArgEditor(ArgPointer arg, QWidget *parent, Converter converter)
    : QWidget{parent},
      text{new QLabel{this}},
      popup{new QListWidget{this}}
{
//    move(parent->pos());
    setAttribute(Qt::WA_DeleteOnClose);
    mArg = arg;
    mConverter = converter;
    constexpr int padding = 50;
    auto p = new QBoxLayout{QBoxLayout::LeftToRight, this};
    p->addWidget(text);
    p->setContentsMargins(0, 0, 0, 0);
    text->setFixedHeight(text->fontMetrics().height() + padding);
    popup->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->setWindowFlags(Qt::Popup);
    popup->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

    resize(parent->size());
    connect(popup, &QListWidget::currentTextChanged, text, &QLabel::setText);
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
        auto idx = popup->currentRow() + 1 == popup->count() ?
                   0 : popup->currentRow() + 1;
        popup->setCurrentRow(idx);
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(popup->currentRow() + mLower);

        popup->scrollToItem(popup->currentItem(), QAbstractItemView::PositionAtCenter);
        break;
    }
    case Qt::Key_Minus:
    {
        auto idx = popup->currentRow() - 1 < 0 ?
                    popup->count() - 1 : popup->currentRow() - 1;
        popup->setCurrentRow(idx);
        if(mArg->commitPolicy() == DeviceArg::CommitPolicy::Immediate)
            mArg->setValue(popup->currentRow() + mLower);

        popup->scrollToItem(popup->currentItem(), QAbstractItemView::PositionAtCenter);
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
        mArg->setValue(popup->currentRow() + mLower);
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
    popup->clear();

    auto translated = QtConcurrent::blockingMapped(list, mConverter);
    for(int i = mLower; i <= range.second; ++i)
    {
        popup->addItem(translated[i]);
    }

    popup->setCurrentRow(mArg->currentValue() - mLower);

    popup->move(mapToGlobal(text->geometry().bottomLeft()));

//    setStyleSheet("background: gray");
    setStyleSheet(".QLabel{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:0.5 rgba(0, 0, 0, 127), stop:1 rgba(0, 0, 0, 0));}");

//    popup->hide();
    grabKeyboard();
}

void EnumArgEditor::hideEvent(QHideEvent *)
{
    releaseKeyboard();
}

void EnumArgEditor::resizeEvent(QResizeEvent *)
{
    popup->setFixedWidth(text->geometry().width());
}

void EnumArgEditor::moveEvent(QMoveEvent *)
{
    popup->move(mapToGlobal(text->geometry().bottomLeft()));
}

}
