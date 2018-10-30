#include "desktop.h"
#include <QApplication>
#include <globalmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GlobalManager::instance()->applyTranslation(R"(C:\Users\joyqa\Documents\git\flawdetector\flawdetector\zh_cn.qm)");

//    a.setStyleSheet("QLabel{font: 24px;}");
    a.setStyleSheet(R"(
                    QLabel{font: 18pt;}
                    .Component--EnumArgEditor{
                    background: yellow;
                    }
                    .Component--EnumArgEditor QLabel{
                    background: cyan;
                    }
                    .Component--ItemWheel{
                    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
                    stop:0 rgba(0, 0, 0, 0),
                    stop:0.5 rgba(0, 0, 0, 100),
                    stop:1 rgba(0, 0, 0, 0));
                    }
                    .Component--ItemWheel QWidget#selection{
                    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
                    stop:0 rgba(0, 0, 0, 100),
                    stop:0.5 rgba(0, 0, 0, 0),
                    stop:1 rgba(0, 0, 0, 100));
                    }
                    QWidget{
                    border: none;
                    }
                    )");

    Desktop w;
    w.show();

    return a.exec();
}
