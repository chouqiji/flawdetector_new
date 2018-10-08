#include "globalmanager.h"
#include "devicearg.h"

GlobalManager GlobalManager::m_instance;

GlobalManager::GlobalManager()
{

}

GlobalManager::~GlobalManager()
{

}

GlobalManager *GlobalManager::instance()
{
    return &m_instance;
}
