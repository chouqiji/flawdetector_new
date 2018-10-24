#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "component/simpleinspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/enumerablearg.h"
#include "component/enumargeditor.h"
#include "component/itemwheel.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);

    auto p = GlobalManager::instance()->getEnumerableArg<QString>("name");

    auto pw1 = new Component::SimpleInspector(this);
    auto pw2 = new Component::SimpleInspector(this);

    pw1->bind(p, [p](auto in){return new Component::EnumArgEditor(p, in);});
    pw2->bind(p, nullptr, [](auto in){return in.toString().append("233");});

    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw1);
    pl->addWidget(pw2);

    auto psc = new QShortcut(Qt::Key_F1, pw1);
    connect(psc, &QShortcut::activated, pw1, &Component::SimpleInspector::activateEditor);
}

Desktop::~Desktop()
{

}
