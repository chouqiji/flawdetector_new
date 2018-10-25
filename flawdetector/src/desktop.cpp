#include "desktop.h"
#include "globalmanager.h"
#include <QDebug>
#include "component/simpleinspector.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QComboBox>
#include "devicearg/enumerablearg.h"
#include "component/enumargeditor.h"
#include "component/numericargeditor.h"
#include "devicearg/numericarg.h"

Desktop::Desktop(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800, 480);

    auto p = GlobalManager::instance()->getEnumerableArg<QString>("name");

    auto pw1 = new Component::SimpleInspector(this);
    auto pw2 = new Component::SimpleInspector(this);

    pw1->bind(p, [p](auto in){
        using namespace Component;
        return new EnumArgEditor{p, in, defaultConverter,
                                PopupMode::Relative, 3};
    });
    pw2->bind(p, nullptr, [](auto in){return in.toString().append("233");});

    auto pl = new QBoxLayout(QBoxLayout::TopToBottom, this);
    pl->addWidget(pw1);
    pl->addWidget(pw2);

    auto psc = new QShortcut(Qt::Key_F1, pw1);
    connect(psc, &QShortcut::activated, pw1, &Component::SimpleInspector::setFocus);

    auto p_gain = GlobalManager::instance()->getNumericArg<int>("gain");
    auto pw_gain = new Component::SimpleInspector(this);
    pw_gain->bind(p_gain);
    pl->addWidget(pw_gain);
    auto psc_gain = new QShortcut(Qt::Key_F2,pw_gain);
    connect(psc_gain,&QShortcut::activated,pw_gain,&Component::SimpleInspector::actEditor);

    auto p_range = GlobalManager::instance()->getNumericArg<double>("range");
    auto pw_range = new Component::SimpleInspector(this);
    pw_range->bind(p_range);
    pl->addWidget(pw_range);
    auto psc_range = new QShortcut(Qt::Key_F3,pw_range);
    connect(psc_range,&QShortcut::activated,pw_range,&Component::SimpleInspector::actdoubleEditor);

}

Desktop::~Desktop()
{

}
