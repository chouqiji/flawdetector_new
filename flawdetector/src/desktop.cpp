#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "arginspector.h"
#include <QBoxLayout>

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    auto p = GlobalManager::instance()->getDeviceArg<QString>("test");
    if(!p.isNull())
    {
        qDebug()<<p->range();
        p->setRange({"r1","r2"});
        qDebug()<<p->range();
    }
    auto pw = new ArgInspector(this);
    pw->bind(p);
    auto pl = new QBoxLayout(QBoxLayout::LeftToRight, this);
    pl->addWidget(pw);
}

Desktop::~Desktop()
{

}
