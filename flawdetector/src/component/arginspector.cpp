#include "arginspector.h"
#include <QLabel>
#include <QBoxLayout>

using namespace Component;

template <typename T>
class Component::ImplArgInspector
{
public:
    ImplArgInspector(ArgInspector<T>* parent);

    using PtrArg_t = QSharedPointer<DeviceArg::IDeviceArg<T>>;
    PtrArg_t arg;
    QLabel *mName;
    QLabel *mUnit;
    QLabel *mValue;
    QBoxLayout *mLayout;

private:
    ArgInspector<T>* mPtrParent;
};

template <typename T>
ImplArgInspector<T>::ImplArgInspector(ArgInspector<T> *parent)
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

template <typename T>
ArgInspector<T>::ArgInspector(QWidget *parent)
    : QWidget{parent},
      pImpl{new ImplArgInspector<T>{this}}
{

}

template <typename T>
ArgInspector<T>::~ArgInspector()
{

}

template <typename T>
void ArgInspector<T>::bind(PtrArg_t arg)
{
    pImpl->mName->setText(arg->argName());
    pImpl->mValue->setText(arg->value());
    pImpl->mUnit->setText(arg->unit());
    pImpl->arg = arg;
    connect(arg.data(), &DeviceArg::IDeviceArgSignals::updated, this, &ArgInspector::updateValue);
}

template <typename T>
void ArgInspector<T>::updateValue()
{
    pImpl->mValue->setText(pImpl->arg->value());
}

// instantiate
template class ArgInspector<QString>;
template class ArgInspector<int>;
template class ArgInspector<float>;
