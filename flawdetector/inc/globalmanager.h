#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

class ImplGlobalManager;

class GlobalManager : public QObject
{
    Q_OBJECT

public:
    static GlobalManager* instance();

//    template <typename T>
//    using DevArgPtr = QSharedPointer<DeviceArg::IDeviceArg<T>>;
//    template <typename T>
//    DevArgPtr<T> getDeviceArg(const QString& argToken);

private:
    static GlobalManager mInstance;

    QScopedPointer<ImplGlobalManager> pImpl;

    void updateSettings(const QString&, const QVariant&);

    GlobalManager();
    ~GlobalManager();
    GlobalManager(const GlobalManager&) = delete;
    GlobalManager& operator=(const GlobalManager&) = delete;
};

#endif // GLOBALMANAGER_H
