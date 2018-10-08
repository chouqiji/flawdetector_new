#include "globalmanager.h"
#include "devicearg.h"
#include <QDebug>

GlobalManager GlobalManager::m_instance;

GlobalManager::GlobalManager()
{
    using namespace DeviceArg;
    QString str{"hello world"};
    auto arg = makeArg<QString>(str);
    qDebug()<<arg->value();
}

GlobalManager::~GlobalManager()
{

}

GlobalManager *GlobalManager::instance()
{
    return &m_instance;
}
