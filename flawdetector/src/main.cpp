#include "desktop.h"
#include <QApplication>
#include <globalmanager.h>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile *f = new QFile(":/theme/style.qss");
    f->open(QFile::ReadOnly);
    a.setStyleSheet(QLatin1String(f->readAll()));
    delete f;

    GlobalManager::instance()->applyTranslation(R"(C:\Users\joyqa\Documents\git\flawdetector\flawdetector\zh_cn.qm)");

    Desktop w;
    w.show();

    return a.exec();
}
