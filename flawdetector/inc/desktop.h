#ifndef DESKTOP_H
#define DESKTOP_H

#include <QMainWindow>

class Desktop : public QMainWindow
{
    Q_OBJECT

public:
    Desktop(QWidget *parent = 0);
    ~Desktop();
};

#endif // DESKTOP_H
