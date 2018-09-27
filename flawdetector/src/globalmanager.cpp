#include "globalmanager.h"
#include "devarg/deviceargs.h"

GlobalManager::GlobalManager(QObject *parent) : QObject(parent)
{
    // we'd like to use:
    DeviceArgs::MakeArg();
}
