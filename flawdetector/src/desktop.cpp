#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>

Desktop::Desktop(QWidget *parent)
    : QMainWindow(parent)
{
    auto p = GlobalManager::instance()->getDeviceArg<QString>("test");
    if(!p.isNull())
    {
        qDebug()<<p->range();
        p->setRange({"r1","r2"});
        qDebug()<<p->range();
    }
}

Desktop::~Desktop()
{

}
