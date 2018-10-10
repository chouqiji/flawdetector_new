#include "arginspector.h"
#include <QLabel>
#include <QBoxLayout>

namespace Component {

template <typename T>
class ImplArgInspector
{
public:
    ImplArgInspector(ArgInspector<T>* parent)
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

    using PtrArg_t = QSharedPointer<DeviceArg::IDeviceArg<T>>;
    PtrArg_t arg;
    QLabel *mName;
    QLabel *mUnit;
    QLabel *mValue;
    QBoxLayout *mLayout;

    void setName(const QString &name)
    {
        mName->setText(name);
    }

    void setUnit(const QString &unit)
    {
        mUnit->setText(unit);
    }

    void setValue(const T &value);

private:
    ArgInspector<T>* mPtrParent;
};

template <typename T>
void ImplArgInspector<T>::setValue(const T &value)
{
    mValue->setText(value);
}

template<>
void ImplArgInspector<int>::setValue(const int &value)
{
    mValue->setText(QString::number(value));
}

template<>
void ImplArgInspector<float>::setValue(const float &value)
{
    // FIXME: precision
    mValue->setText(QString::number(value, 'f', 1));
}

} // namespace

using namespace Component;

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
    pImpl->setName(arg->argName());
    pImpl->setValue(arg->value());
    pImpl->setUnit(arg->unit());
    pImpl->arg = arg;
    connect(arg.data(), &DeviceArg::IDeviceArgSignals::updated, this, &ArgInspector::updateValue);
}

template <typename T>
void ArgInspector<T>::updateValue()
{
    pImpl->setValue(pImpl->arg->value());
}

// instantiate
template class ArgInspector<QString>;
template class ArgInspector<int>;
template class ArgInspector<float>;
