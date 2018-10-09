#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>
#include "devicearg.h"

class ImplGlobalManager;

class GlobalManager : public QObject
{
    Q_OBJECT
private:
    static GlobalManager m_instance;
    GlobalManager();
    ~GlobalManager();
    GlobalManager(const GlobalManager&) = delete;
    GlobalManager& operator=(const GlobalManager&) = delete;
    QScopedPointer<ImplGlobalManager> pImpl;

public:
    static GlobalManager* instance();

    template <typename T>
    using DevArgPtr = QSharedPointer<DeviceArg::IDeviceArg<T>>;
    template <typename T>
    DevArgPtr<T> getDeviceArg(const QString& argToken);

    void setDeviceArgByIndex(const QString& argToken, const unsigned int& value);
    void setDeviceArg(const QString& argToken, const QString& value);
    void setDeviceArg(const QString& argToken, const int& value);
    void setDeviceArg(const QString& argToken, const float& value);
};

#endif // GLOBALMANAGER_H
