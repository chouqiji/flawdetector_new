#include "arginspector.h"
#include <QLabel>
#include <QBoxLayout>

using namespace Component;

class Component::ImplArgInspector
{
public:
    ImplArgInspector(ArgInspector* parent);
    ArgInspector::PtrStrArg_t arg;
    QLabel *mName;
    QLabel *mUnit;
    QLabel *mValue;
    QBoxLayout *mLayout;

private:
    ArgInspector* mPtrParent;
};

ImplArgInspector::ImplArgInspector(ArgInspector *parent)
    : mPtrParent{parent}
{
    mLayout = new QBoxLayout{QBoxLayout::LeftToRight, mPtrParent};
    mName = new QLabel{mPtrParent};
    mValue = new QLabel{mPtrParent};
    mUnit = new QLabel{mPtrParent};
    mLayout->addWidget(mName, 30);
    mLayout->addWidget(mValue, 60);
    mLayout->addWidget(mUnit, 10);
}

ArgInspector::ArgInspector(QWidget *parent)
    : QWidget{parent},
      pImpl{new ImplArgInspector{this}}
{

}

ArgInspector::~ArgInspector()
{

}

void ArgInspector::bind(ArgInspector::PtrStrArg_t arg)
{
    pImpl->mName->setText(arg->argName());
    pImpl->mValue->setText(arg->value());
    pImpl->mUnit->setText(arg->unit());
    pImpl->arg = arg;
    connect(arg.data(), &DeviceArg::IDeviceArgSignals::updated, this, &ArgInspector::updateValue);
}

void ArgInspector::updateValue()
{
    pImpl->mValue->setText(pImpl->arg->value());
}
