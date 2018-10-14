#include "globalmanager.h"
#include <QHash>

class ImplGlobalManager
{
public:
    using RawPointer = QSharedPointer<DeviceArg::IDeviceArgSignals>;

    ImplGlobalManager(GlobalManager* parent);
    RawPointer getDeviceArg(const QString &argToken);

private:
    using TokenType = QString;
    using Dictionary_t = QHash<TokenType, RawPointer>;

    Dictionary_t   mDictionary;

    GlobalManager* mPtrParent;
};

ImplGlobalManager::ImplGlobalManager(GlobalManager *parent) : mPtrParent{parent}
{
    using namespace DeviceArg;

    mDictionary["test"] =  makeArg<QString>(
                            {"name",
                             "value1",
                             {"value1", "value2", "value3"},
                             "unit",
                             CommitPolicy::Immediate,
                             nullptr}
                           , mPtrParent);

}

ImplGlobalManager::RawPointer ImplGlobalManager::getDeviceArg(const QString& argToken)
{
    return mDictionary.value(argToken, ImplGlobalManager::RawPointer{});
}

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

template<typename T>
GlobalManager::DevArgPtr<T> GlobalManager::getDeviceArg(const QString &argToken)
{
    return pImpl->getDeviceArg(std::forward<const QString>(argToken)).dynamicCast<DeviceArg::IDeviceArg<T>>();
}

// instantiation
template GlobalManager::DevArgPtr<QString> GlobalManager::getDeviceArg(const QString&);
template GlobalManager::DevArgPtr<int> GlobalManager::getDeviceArg(const QString&);
template GlobalManager::DevArgPtr<float> GlobalManager::getDeviceArg(const QString&);
