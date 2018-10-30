#include "component/private/itemwheel.h"
#include <QBoxLayout>
#include <QLabel>
#include <QVariant>
#include <QDebug>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QScrollBar>
#include <component/common.h>

namespace Component {

class ItemWheel::Impl
{
public:
    Impl(ItemWheel *p) : mPtr{p} { }
    ~Impl() {}
    void informStringChange() {
        emit mPtr->currentTextChanged(mLabels[mIndex]->text());
    }
    void animatedScrollTo(int fromIndex, int toIndex) {
        auto p = new QPropertyAnimation(mPtr->verticalScrollBar(), "value");
        p->setDuration(100);
        p->setStartValue(mScrollStep * fromIndex);
        p->setEndValue(mScrollStep * toIndex);
        p->start();
        mIndex = toIndex;

        informStringChange();
    }
    void addPadding(int itemHeight)
    {
        auto layout = static_cast<QBoxLayout*>(mWidget->layout());

        // Tail spacing
        layout->addSpacing(itemHeight * mPaddingSize);
        // Head spacing
        layout->insertSpacing(0, itemHeight * mPaddingSize);
    }
    void setViewportSize(int viewportSize)
    {
        mViewportSize = viewportSize;
        mPaddingSize = viewportSize / 2;
    }

    ItemWheel* mPtr;
    QList<QLabel*> mLabels;
    QWidget *mWidget;
    QWidget *mSelection;
    int mIndex;
    int mListSize;
    int mScrollStep;
    int mViewportSize;
    int mPaddingSize;
};

ItemWheel::ItemWheel(int viewportSize, QWidget *parent)
    : QScrollArea(parent)
    , pImpl{new Impl{this}}
{
    assert(viewportSize & 0b1);
    pImpl->setViewportSize(viewportSize);

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
    layout->setContentsMargins(0, 0, 0, 0);
}

ItemWheel::~ItemWheel()
{
}

void ItemWheel::selectNext()
{
    pImpl->animatedScrollTo(pImpl->mIndex, limitUp(pImpl->mIndex + 1, pImpl->mListSize - 1));
}

void ItemWheel::selectPrev()
{
    pImpl->animatedScrollTo(pImpl->mIndex, limitDown(pImpl->mIndex - 1, 0));
}

int ItemWheel::currentIndex() const
{
    return pImpl->mIndex;
}

void ItemWheel::setIndex(int index)
{
    pImpl->mIndex = index;
    pImpl->informStringChange();
}

void ItemWheel::setList(const QStringList &list)
{
    pImpl->mLabels.reserve(list.count());
    auto layout = pImpl->mWidget->layout();
    for(auto & ele : list)
    {
        auto p = new QLabel(pImpl->mWidget);
        layout->addWidget(p);
        p->setText(ele);
        pImpl->mLabels<<p;
    }

    pImpl->mListSize = list.size();
}

void ItemWheel::showEvent(QShowEvent *)
{
    pImpl->mScrollStep = pImpl->mLabels[0]->fontMetrics().lineSpacing();
    auto itemHeight = pImpl->mScrollStep;
    for(auto &p: pImpl->mLabels)
        p->setFixedHeight(itemHeight);

    setFixedHeight(itemHeight * pImpl->mViewportSize);

    pImpl->mWidget->setFixedWidth(width());

    pImpl->addPadding(itemHeight);

    setWidget(pImpl->mWidget);

    verticalScrollBar()->setValue(pImpl->mScrollStep * pImpl->mIndex);

    pImpl->mSelection->raise();
    pImpl->mSelection->resize(pImpl->mLabels[0]->size());
    pImpl->mSelection->move(0, (height() - itemHeight) / 2);
}

}
