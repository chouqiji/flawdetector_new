#include "component/arginspector.h"

namespace Component {

void ArgInspector::bind(ArgInspector::ArgPointer pArg, Converter converter)
{
    mArgPointer = pArg;
    mConverter = converter;

    updateName(mArgPointer->displayedName());
    updateUnit(mArgPointer->displayedUnit());
    updateValue(mArgPointer->value());

    connect(mArgPointer.data(), &DeviceArg::ViewPort::valueChanged, this, &ArgInspector::updateValue);
    connect(mArgPointer.data(), &DeviceArg::ViewPort::nameChanged, this, &ArgInspector::updateName);
    connect(mArgPointer.data(), &DeviceArg::ViewPort::unitChanged, this, &ArgInspector::updateUnit);
}

} // namespace
