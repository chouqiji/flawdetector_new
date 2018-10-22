#include "globalmanager.h"
#include <QHash>
#include <QDebug>
#include <QSettings>
#include <QMutexLocker>

class ImplGlobalManager
{
public:
    ImplGlobalManager(GlobalManager* parent);
    QSettings  mSettings{"set.ini", QSettings::IniFormat};

private:
    using TokenType = QString;

    GlobalManager* mPtrParent;
};

ImplGlobalManager::ImplGlobalManager(GlobalManager *parent) : mPtrParent{parent}
{
//    using namespace DeviceArg;

//    DeviceArgInitList<QString> pww{"test",
//              0,
//              "unit",
//              {"value1", "value2", "value3"},
//              static_cast<CommitPolicy>(0),
//              nullptr};

//    mDictionary["test"] =  makeEnumerableArg(
//                            std::move(pww)
//                           , mPtrParent);

//    mDictionary["tfloat"] =  makeNumericArg<float>(
//                            {QT_TR_NOOP("name2"),
//                             1.0,
//                             "unit",
//                             {0.1f, 1.1f},
//                             CommitPolicy::Immediate,
//                             nullptr}
//                           , mPtrParent);

//    for(const auto& p : mDictionary)
//        QObject::connect(p.data(), &IDeviceArgSignals::settingChanged, mPtrParent, &GlobalManager::updateSettings);

//    auto restriction = [&](){
//        auto a = mDictionary["tfloat"].dynamicCast<IDeviceArg<float>>()->value();
//        mDictionary["test"].dynamicCast<IDeviceArg<QString>>()->setValue(0);
//    };

//    QObject::connect(mDictionary["tfloat"].data(), &IDeviceArgSignals::valueChanged, restriction);
}

GlobalManager::GlobalManager() : pImpl{new ImplGlobalManager{this}}
{
}

GlobalManager::~GlobalManager()
{

}

GlobalManager GlobalManager::mInstance;

GlobalManager* GlobalManager::instance()
{
    return &mInstance;
}

void GlobalManager::updateSettings(const QString &s, const QVariant &v)
{
    if(v.canConvert<QVariantList>())
        pImpl->mSettings.setValue(s, v.value<QVariantList>());
    else
        pImpl->mSettings.setValue(s, v);
}

//template<typename T>
//GlobalManager::DevArgPtr<T> GlobalManager::getDeviceArg(const QString &argToken)
//{
//    return pImpl->getDeviceArg(std::forward<const QString>(argToken)).dynamicCast<DeviceArg::IDeviceArg<T>>();
//}

//// instantiation
//template GlobalManager::DevArgPtr<QString> GlobalManager::getDeviceArg(const QString&);
//template GlobalManager::DevArgPtr<int> GlobalManager::getDeviceArg(const QString&);
//template GlobalManager::DevArgPtr<float> GlobalManager::getDeviceArg(const QString&);
