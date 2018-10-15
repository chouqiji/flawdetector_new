#include "globalmanager.h"
#include <QHash>
#include <QDebug>
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

    mDictionary["tfloat"] =  makeArg<float>(
                            {"tfloat",
                             QT_TR_NOOP("name2"),
                             1.0,
                             {0.1, 1.1},
                             "unit",
                             CommitPolicy::Immediate,
                             nullptr}
                           , mPtrParent);

    for(const auto& p : mDictionary)
        QObject::connect(p.data(), IDeviceArgSignals::settingChanged, mPtrParent, GlobalManager::updateSettings);

    auto restriction = [&](){
        auto a = mDictionary["tfloat"].dynamicCast<IDeviceArg<float>>()->value();
        mDictionary["test"].dynamicCast<IDeviceArg<QString>>()->setValue(QString::number(a, 'f', 2));
    };

    QObject::connect(mDictionary["tfloat"].data(), IDeviceArgSignals::valueChanged, restriction);
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
    if(v.canConvert<QVariantList>())
        pImpl->mSettings.setValue(s, v.value<QVariantList>());
    else
        pImpl->mSettings.setValue(s, v);
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
