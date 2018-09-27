#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QObject>

class GlobalManager : public QObject
{
    Q_OBJECT
public:
    explicit GlobalManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GLOBALMANAGER_H