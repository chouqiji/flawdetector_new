#include "globalmanager.h"

class ImplGlobalManager
{
public:
    ImplGlobalManager(GlobalManager* parent) : mPtrParent{parent}
    {
    }

private:
    GlobalManager* mPtrParent;
};

GlobalManager GlobalManager::m_instance;

GlobalManager::GlobalManager() : pImpl{new ImplGlobalManager{this}}
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
