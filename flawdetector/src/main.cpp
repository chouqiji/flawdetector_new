#include "desktop.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(R"(C:\Users\joyqa\Documents\git\flawdetector\flawdetector\zh_cn.qm)");
    a.installTranslator(&translator);

    Desktop w;
    w.show();

    return a.exec();
}
