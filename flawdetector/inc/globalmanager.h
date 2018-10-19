#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

class ImplGlobalManager;

class GlobalManager : public QObject
{
    Q_OBJECT
private:
    static GlobalManager *mInstance;
    GlobalManager();
    ~GlobalManager();
    GlobalManager(const GlobalManager&) = delete;
    GlobalManager& operator=(const GlobalManager&) = delete;
    QScopedPointer<ImplGlobalManager> pImpl;

public:
    static GlobalManager* instance();

//    template <typename T>
//    using DevArgPtr = QSharedPointer<DeviceArg::IDeviceArg<T>>;
//    template <typename T>
//    DevArgPtr<T> getDeviceArg(const QString& argToken);

public slots:
    void updateSettings(const QString&, const QVariant&);
};

#endif // GLOBALMANAGER_H
