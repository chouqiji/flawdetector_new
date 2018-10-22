#include "desktop.h"
#include <QApplication>
#include <globalmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GlobalManager::instance()->applyTranslation(R"(C:\Users\joyqa\Documents\git\flawdetector\flawdetector\zh_cn.qm)");

    Desktop w;
    w.show();

    return a.exec();
}
