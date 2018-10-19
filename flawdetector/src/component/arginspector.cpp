#include "arginspector.h"
#include <QLabel>
#include <QBoxLayout>
#include <QVariant>

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

    using PtrArg = typename ArgInspector<T>::PtrArg;
    PtrArg arg;
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

template <>
void ArgInspector<QString>::bind(PtrArg arg)
{
    pImpl->setName(arg->displayedName());
//    pImpl->setValue(arg->value());
    pImpl->setUnit(arg->displayedUnit());
    pImpl->arg = arg;
    arg->connect(&DeviceArg::Signals::valueChanged, this, [](){qDebug("233");});
    arg->connect(&DeviceArg::Signals::valueChanged, this, &ArgInspector<QString>::updateValue);
}

template <typename T>
void ArgInspector<T>::updateValue()
{
    pImpl->setValue(pImpl->arg->value().toString());
}

// instantiate
template class ArgInspector<QString>;
} // namespace
