#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "arginspector.h"
#include <QBoxLayout>
#include <QShortcut>

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    auto p = GlobalManager::instance()->getDeviceArg<QString>("test");
    //if(!p.isNull())

    auto pw = new Component::ArgInspector<QString>(this);
    pw->bind(p);
    auto sc = new QShortcut(Qt::Key_F1, pw);
    connect(sc, QShortcut::activated, [](){qDebug()<<"wow";});
    auto pw2 = new Component::ArgInspector<QString>(this);
    pw2->bind(p);
    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw);
    pl->addWidget(pw2);
    p->setValue("value2");
    p->setRange({"valuex, valuey"});

    auto u = GlobalManager::instance()->getDeviceArg<float>("tfloat");
    u->setRange({0.3, 0.5});
    u->setValue(11.0);
}

Desktop::~Desktop()
{

}
