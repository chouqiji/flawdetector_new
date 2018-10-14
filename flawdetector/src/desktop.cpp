#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "arginspector.h"
#include <QBoxLayout>

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    auto p = GlobalManager::instance()->getDeviceArg<QString>("test");
    //if(!p.isNull())

    auto pw = new Component::ArgInspector<QString>(this);
    pw->bind(p);
    auto pw2 = new Component::ArgInspector<QString>(this);
    pw2->bind(p);
    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw);
    pl->addWidget(pw2);
    p->setValue("value2");
    p->setRange({"valuex, valuey"});

    auto u = GlobalManager::instance()->getDeviceArg<float>("tfloat");
    u->setRange({0.3, 0.5});
}

Desktop::~Desktop()
{

}
