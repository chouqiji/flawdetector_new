#include "component/itemwheel.h"
#include <QBoxLayout>
#include <QLabel>
#include <QVariant>
#include <QDebug>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <component/common.h>

namespace Component {

class ItemWheel::ImplItemWheel
{
public:
    ImplItemWheel(ItemWheel *p) : mPtr{p} { }
    ~ImplItemWheel() {}
    void assignStrings() {
        emit mPtr->currentTextChanged(mLabels[mIndex]->text());
    }

    ItemWheel* mPtr;
    QList<QLabel*> mLabels;
    QWidget *mWidget;
    QWidget *mSelection;
    int mIndex;
    int mSize;
    int mStep;
    int mViewportSize;
};

ItemWheel::ItemWheel(int viewportSize, QWidget *parent)
    : QScrollArea(parent)
    , pImpl{new ImplItemWheel{this}}
{
    assert(viewportSize & 0b1);
    pImpl->mViewportSize = viewportSize;

    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pImpl->mSelection = new QFrame(viewport());
    pImpl->mSelection->setObjectName("selection");

    pImpl->mWidget = new QFrame(this);
    pImpl->mWidget->setStyleSheet("background:transparent");

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, pImpl->mWidget);

    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
}

ItemWheel::~ItemWheel()
{
}

void ItemWheel::selectNext()
{
    pImpl->mIndex = limitUp(pImpl->mIndex + 1, pImpl->mSize - 1);
    pImpl->assignStrings();
    auto p = new QPropertyAnimation(verticalScrollBar(), "value");
    p->setEasingCurve(QEasingCurve(QEasingCurve::OutBack));
    p->setDuration(100);
    p->setStartValue(pImpl->mStep * (pImpl->mIndex-1));
    p->setEndValue(pImpl->mStep * pImpl->mIndex);
    p->start();
}

void ItemWheel::selectPrev()
{
    pImpl->mIndex = limitDown(pImpl->mIndex - 1, 0);
    pImpl->assignStrings();
    auto p = new QPropertyAnimation(verticalScrollBar(), "value");
    p->setEasingCurve(QEasingCurve(QEasingCurve::OutBack));
    p->setDuration(100);
    p->setStartValue(pImpl->mStep * (pImpl->mIndex+1));
    p->setEndValue(pImpl->mStep * pImpl->mIndex);
    p->start();
}

int ItemWheel::currentIndex() const
{
    return pImpl->mIndex;
}

void ItemWheel::setIndex(int index)
{
    pImpl->mIndex = index;
    pImpl->assignStrings();
}

void ItemWheel::setList(const QStringList &list)
{
    pImpl->mLabels.reserve(list.count());
    for(auto & ele : list)
    {
        auto p = new QLabel(pImpl->mWidget);
        pImpl->mWidget->layout()->addWidget(p);
        p->setText(ele);
        pImpl->mLabels<<p;
    }

    pImpl->mSize = list.size();
}

void ItemWheel::showEvent(QShowEvent *)
{
    pImpl->mStep = pImpl->mLabels[0]->fontMetrics().lineSpacing();
    auto itemHeight = pImpl->mStep;
    for(auto &p: pImpl->mLabels)
    {
        p->setFixedHeight(itemHeight);
    }

    setFixedHeight(itemHeight * pImpl->mViewportSize);

    pImpl->mWidget->setFixedWidth(width());
    static_cast<QBoxLayout*>(pImpl->mWidget->layout())->addSpacing(itemHeight * (pImpl->mViewportSize / 2));
    static_cast<QBoxLayout*>(pImpl->mWidget->layout())->insertSpacing(0, itemHeight * (pImpl->mViewportSize / 2));

    setWidget(pImpl->mWidget);

    verticalScrollBar()->setValue(pImpl->mStep * pImpl->mIndex);

    pImpl->mSelection->raise();
    pImpl->mSelection->resize(pImpl->mLabels[0]->size());
    pImpl->mSelection->move(0, (height() - itemHeight)/2);
}

}
