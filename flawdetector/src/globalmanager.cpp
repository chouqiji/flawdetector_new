#include "globalmanager.h"
#include <QMap>

template <typename T>
using DevArgPtr = QSharedPointer<DeviceArg::IDeviceArg<T>>;

class ImplGlobalManager
{
public:
    ImplGlobalManager(GlobalManager* parent);
template <typename T>
    DevArgPtr<T> getDeviceArg(const QString &argToken);

private:
    typedef QString TokenType;
    typedef QMap<TokenType, DevArgPtr<QString>> strArgDict_t;
    typedef QMap<TokenType, DevArgPtr<int>>     intArgDict_t;
    typedef QMap<TokenType, DevArgPtr<float>>   floatArgDict_t;

    strArgDict_t   mStrArgDict;
    intArgDict_t   mIntArgDict;
    floatArgDict_t mFloatArgDict;

    GlobalManager* mPtrParent;
};

ImplGlobalManager::ImplGlobalManager(GlobalManager *parent) : mPtrParent{parent}
{
    using namespace DeviceArg;

    mStrArgDict["test"] =  makeArg<QString>({
                             "name",
                             "value1",
                             {"value1", "value2", "value3"},
                             "unit",
                             CommitPolicy::Immediate,
                             [](const QString&){
                                    return;
                             }
                           });
}

template<typename T>
DevArgPtr<T> ImplGlobalManager::getDeviceArg(const QString&)
{
    return DevArgPtr<T>(nullptr);
}

template<>
DevArgPtr<QString> ImplGlobalManager::getDeviceArg(const QString &argToken)
{
    return mStrArgDict.value(argToken);
}

template<>
DevArgPtr<int> ImplGlobalManager::getDeviceArg(const QString &argToken)
{
    return mIntArgDict.value(argToken);
}

template<>
DevArgPtr<float> ImplGlobalManager::getDeviceArg(const QString &argToken)
{
    return mFloatArgDict.value(argToken);
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
DevArgPtr<T> GlobalManager::getDeviceArg(const QString &argToken)
{
    return pImpl->getDeviceArg<T>(std::forward<const QString>(argToken));
}

// instantiation
template DevArgPtr<QString> GlobalManager::getDeviceArg(const QString&);
template DevArgPtr<int> GlobalManager::getDeviceArg(const QString&);
template DevArgPtr<float> GlobalManager::getDeviceArg(const QString&);
