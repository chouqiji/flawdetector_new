#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

namespace DeviceArg {

template <typename T>
class EnumerableArg;

template <typename T>
class NumericArg;

}

class ImplGlobalManager;

class GlobalManager : public QObject
{
    Q_OBJECT

public:
    static GlobalManager* instance();

    void applyTranslation(const QString & translationFileName);
    void updateSettings(const QString&, const QVariant&);

    template <typename T>
    using EnumArgPtr = QSharedPointer<DeviceArg::EnumerableArg<T>>;
    template <typename T>
    using NumArgPtr = QSharedPointer<DeviceArg::NumericArg<T>>;
    template <typename T>
    EnumArgPtr<T> getEnumerableArg(const QString& argName);
    template <typename T>
    NumArgPtr<T> getNumericArg(const QString& argName);

private:
    static GlobalManager mInstance;

    QScopedPointer<ImplGlobalManager> pImpl;

    GlobalManager();
    ~GlobalManager();
    GlobalManager(const GlobalManager&) = delete;
    GlobalManager& operator=(const GlobalManager&) = delete;
};

#endif // GLOBALMANAGER_H
