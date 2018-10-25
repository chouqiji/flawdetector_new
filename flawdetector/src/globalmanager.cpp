#include "globalmanager.h"
#include <QDebug>
#include <QSettings>
#include <QHash>
#include <QCoreApplication>
#include <QTranslator>
#include <devicearg/enumerablearg.h>
#include <devicearg/numericarg.h>

class ImplGlobalManager
{
public:
    ImplGlobalManager(GlobalManager* parent);
    QSettings  mSettings{"set.ini", QSettings::IniFormat};

    using TokenType = QString;
    using DictType = QHash<QString, QSharedPointer<DeviceArg::BasicViewPort>>;

    DictType mDict;
    QTranslator translator;

private:
    GlobalManager* mPtrParent;
};

ImplGlobalManager::ImplGlobalManager(GlobalManager *parent) : mPtrParent{parent}
{
    using namespace DeviceArg;

    mDict["name"] = makeArg<QString>("name", "unit", {1,{1,6},{QT_TR_NOOP("name2"), "www", "hhh", "aaa", "bbb", "ccc", "ddd"}, CommitPolicy::Immediate, nullptr});

    mDict["gain"] = makeArg<int>("gain","dB",{200,{100,600},CommitPolicy::Immediate, nullptr});

    mDict["range"] = makeArg<double>("range","mm",{200.2,{100.1,600.6},CommitPolicy::Immediate, nullptr});
    for(const auto& p : mDict)
        QObject::connect(p.data(), &BasicViewPort::argChanged, mPtrParent, &GlobalManager::updateSettings);

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

void GlobalManager::applyTranslation(const QString &translationFileName)
{
    pImpl->translator.load(translationFileName);
    QCoreApplication::installTranslator(&pImpl->translator);

    // retranslate
    for(auto &ele: pImpl->mDict)
        ele.dynamicCast<DeviceArg::BasicViewPort>()->retranslate();
}

void GlobalManager::updateSettings(const QString &s, const QVariant &v)
{
    if(v.canConvert<QVariantList>())
        pImpl->mSettings.setValue(s, v.value<QVariantList>());
    else
        pImpl->mSettings.setValue(s, v);
}

template<typename T>
GlobalManager::EnumArgPtr<T> GlobalManager::getEnumerableArg(const QString &argName)
{
    return pImpl->mDict[argName].dynamicCast<DeviceArg::EnumerableArg<T>>();
}

template<typename T>
GlobalManager::NumArgPtr<T> GlobalManager::getNumericArg(const QString &argName)
{
    return pImpl->mDict[argName].dynamicCast<DeviceArg::NumericArg<T>>();
}

template GlobalManager::EnumArgPtr<QString> GlobalManager::getEnumerableArg(const QString &argName);
template GlobalManager::NumArgPtr<int> GlobalManager::getNumericArg(const QString &argName);
template GlobalManager::NumArgPtr<double> GlobalManager::getNumericArg(const QString &argName);
