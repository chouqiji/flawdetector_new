#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "component/simpleinspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/enumerablearg.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);
    auto p = GlobalManager::instance()->getEnumerableArg<QString>("name");

    QList<QSharedPointer<QObject>> list{p};
    qDebug()<<list;
    auto pcast = list.at(0).dynamicCast<DeviceArg::EnumerableArg<QString>>();
    auto pcast2 = list.at(0).dynamicCast<DeviceArg::EnumerableArg<double>>();

    auto pw1 = new Component::SimpleInspector(this);
    auto pw2 = new Component::SimpleInspector(this);

    pw1->bind(p);
    pw2->bind(p, [](const QVariant& in){return in.toString().append("233");});

    auto pe = new QComboBox;
    for(const auto &ele : p->list())
        pe->addItem(ele.toString());
    connect(pe, static_cast<void (QComboBox::*)(const int)>(&QComboBox::currentIndexChanged), std::bind(&DeviceArg::EnumerableArg<QString>::setIndex, p, std::placeholders::_1));

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
