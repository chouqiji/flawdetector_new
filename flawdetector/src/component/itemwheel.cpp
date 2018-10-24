#include "component/itemwheel.h"
#include <QBoxLayout>
#include <QLabel>

namespace Component {

class ItemWheel::ImplItemWheel
{
public:
    ImplItemWheel(ItemWheel *p) : mPtr{p} {}
    ~ImplItemWheel() {}
    void assignStrings() {
        int fillSize = mLabels.size() / 2;
        while(mIndex - fillSize < 0)
            mIndex += mSize;

        for(int i = 0; i < mLabels.size(); ++i)
            mLabels[i]->setText(mList[(mIndex - fillSize + i) % mSize]);

        emit mPtr->currentTextChanged(mList[mIndex % mSize]);
    }

    QList<QLabel*> mLabels;
    QStringList mList;
    ItemWheel* mPtr;
    int mIndex;
    int mSize;
};

ItemWheel::ItemWheel(int count, QWidget *parent)
    : QWidget(parent)
    , pImpl{new ImplItemWheel{this}}
{
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pImpl->mLabels.reserve(count);
    for(int i = 0; i < count; ++i)
    {
        auto p = new QLabel(this);
        pImpl->mLabels<<p;
        p->setFixedHeight(p->fontMetrics().height() + 16);
        layout->addWidget(pImpl->mLabels[i]);
    }
    layout->setSpacing(0);
    layout->setContentsMargins(1,1,1,1);

    pImpl->mLabels[count/2]->setObjectName("focus");
    pImpl->mLabels[count/2]->setStyleSheet("background: cyan");
    setStyleSheet(".QWidget{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(0, 0, 0, 0), stop:0.5 rgba(0, 0, 0, 127), stop:1 rgba(0, 0, 0, 0));}");
}

ItemWheel::~ItemWheel()
{

}

void ItemWheel::selectNext()
{
    ++(pImpl->mIndex);
    pImpl->assignStrings();
}

void ItemWheel::selectPrev()
{
    --(pImpl->mIndex);
    pImpl->assignStrings();
}

int ItemWheel::currentIndex()
{
    return pImpl->mIndex % pImpl->mSize;
}

void ItemWheel::setIndex(int index)
{
    pImpl->mIndex = index;
    pImpl->assignStrings();
}

void ItemWheel::setList(const QStringList &list)
{
    pImpl->mList = list;
    pImpl->mSize = list.size();
}

}
