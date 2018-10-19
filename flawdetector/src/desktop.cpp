#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "arginspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/devicearg.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    auto p = DeviceArg::makeArg<QString>("name", "unit", {1, {QT_TR_NOOP("name2"), "www"}, DeviceArg::CommitPolicy::Immediate, nullptr});

    DeviceArg::InitList<QString, DeviceArg::ArgType::Numeric> ss;

    auto pw = new Component::ArgInspector<QString>(this);
    pw->bind(p);
//    auto sc = new QShortcut(Qt::Key_F1, pw);
//    connect(sc, &QShortcut::activated, [](){qDebug()<<"wow";});
    auto pw2 = new Component::ArgInspector<QString>(this);
    pw2->bind(p);
    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw);
    pl->addWidget(pw2);
    p->setValue(0);
    p->setRange({"valuex", "valuey"});
}

Desktop::~Desktop()
{

}
