#include "globalmanager.h"
#include <QHash>
#include <QSettings>
#include <QMutexLocker>

class ImplGlobalManager
{
public:
    using RawPointer = QSharedPointer<DeviceArg::IDeviceArgSignals>;

    ImplGlobalManager(GlobalManager* parent);
    RawPointer getDeviceArg(const QString &argToken);
    QSettings  mSettings{"set.ini", QSettings::IniFormat};

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
                            {"test",
                             "name2",
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

GlobalManager::GlobalManager() : pImpl{new ImplGlobalManager{this}}
{
}

GlobalManager::~GlobalManager()
{
}

GlobalManager* GlobalManager::mInstance = nullptr;

GlobalManager* GlobalManager::instance()
{
    static bool init = true;
    static QMutex lock;

    QMutexLocker locker(&lock);

    if(init)
    {
        mInstance = new GlobalManager;
        init = false;
    }

    return mInstance;
}

void GlobalManager::updateSettings(const QString &s, const QVariant &v)
{

    qDebug()<< s <<v.value<QVariantList>();

    pImpl->mSettings.setValue(s, v.value<QVariantList>());
    qDebug()<<pImpl->mSettings.value(s);
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
