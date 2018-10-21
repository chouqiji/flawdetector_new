#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "component/simpleinspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/devicearg.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    auto p = DeviceArg::makeArg<QString>("name", "unit", {1, {QT_TR_NOOP("name2"), "www"}, DeviceArg::CommitPolicy::Immediate, nullptr});

    auto pw1 = new Component::SimpleInspector(this);
    auto pw2 = new Component::SimpleInspector(this);

    pw1->bind(p);
    pw2->bind(p, [](const QVariant& in){return in.toString().append("233");});

    auto pe = new QComboBox;
    for(const auto &ele : p->range())
        pe->addItem(ele.toString());
    connect(pe, static_cast<void (QComboBox::*)(const int)>(&QComboBox::currentIndexChanged), std::bind(&DeviceArg::EnumerableEditPort::setIndex, p, std::placeholders::_1));

    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw1);
    pl->addWidget(pw2);

    pw1->setEditor(pe);

    auto psc = new QShortcut(Qt::Key_F1, pw1);
    connect(psc, &QShortcut::activated, pw1, &Component::SimpleInspector::activateEditor);

}

Desktop::~Desktop()
{

}
