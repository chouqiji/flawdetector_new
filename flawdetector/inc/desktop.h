#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>

class Desktop : public QWidget
{
    Q_OBJECT

public:
    Desktop(QWidget *parent = 0);
    ~Desktop();
};

#endif // DESKTOP_H
