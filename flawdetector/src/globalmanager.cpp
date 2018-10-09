#include "globalmanager.h"

class ImplGlobalManager
{
public:
    ImplGlobalManager(GlobalManager* parent) : mPParent{parent} {}

private:
    GlobalManager* mPParent;
};

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

template <typename T>
using DevArgPtr = QSharedPointer<DeviceArg::IDeviceArg<T>>;
template<typename T>
DevArgPtr<T> GlobalManager::getDeviceArg(const QString &argName)
{
    return DevArgPtr<T>(nullptr);
}

// instantiation
template DevArgPtr<QString> GlobalManager::getDeviceArg(const QString &argName);
template DevArgPtr<int> GlobalManager::getDeviceArg(const QString &argName);
template DevArgPtr<float> GlobalManager::getDeviceArg(const QString &argName);
