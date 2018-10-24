#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "component/simpleinspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/enumerablearg.h"
#include "component/enumargeditor.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    this->move(0, 0);
//    this->setWindowFlag(Qt::FramelessWindowHint);
    auto p = GlobalManager::instance()->getEnumerableArg<QString>("name");

    auto pw1 = new Component::SimpleInspector(this);
    auto pw2 = new Component::SimpleInspector(this);

    pw1->bind(p);
    pw2->bind(p, [](const QVariant& in){return in.toString().append("233");});

    auto pe = new Component::EnumArgEditor(this);
    pe->bind(p);
    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw1);
    pl->addWidget(pw2);

//    pe->move(0,0);
//    pe->show();

    pw1->setEditor(pe);

    auto psc = new QShortcut(Qt::Key_F1, pw1);
    connect(psc, &QShortcut::activated, pw1, &Component::SimpleInspector::activateEditor);
}

Desktop::~Desktop()
{

}
