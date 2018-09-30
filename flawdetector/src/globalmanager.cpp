#include "globalmanager.h"
#include "devarg/impl.h"
#include <QDebug>

GlobalManager GlobalManager::m_instance;

GlobalManager::GlobalManager()
{
    using namespace DeviceArg;
    QString str{"hello world"};
    QSharedPointer<IDeviceArg<QString>> arg = makeArg<QString>(str);
    qDebug()<<arg->value();
}

GlobalManager::~GlobalManager()
{

}

GlobalManager *GlobalManager::instance()
{
    return &m_instance;
}
