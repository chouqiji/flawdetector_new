#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

class GlobalManager : public QObject
{
    Q_OBJECT
private:
    static GlobalManager m_instance;
    GlobalManager();
    ~GlobalManager();
    GlobalManager(const GlobalManager&) = delete;
    GlobalManager& operator=(const GlobalManager&) = delete;

public:
    static GlobalManager* instance();
};

#endif // GLOBALMANAGER_H
