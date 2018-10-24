#include "component/arginspector.h"

namespace Component {

void ArgInspector::bind(ArgInspector::ArgPointer pArg, EditorCreator creator, Converter converter)
{
    mArgPointer = pArg;
    mConverter = converter;
    mCreator = creator;

    updateName(mArgPointer->displayedName());
    updateUnit(mArgPointer->displayedUnit());
    updateValue(mArgPointer->value());

    connect(mArgPointer.data(), &DeviceArg::ViewPort::valueChanged, this, &ArgInspector::updateValue);
    connect(mArgPointer.data(), &DeviceArg::ViewPort::nameChanged, this, &ArgInspector::updateName);
    connect(mArgPointer.data(), &DeviceArg::ViewPort::unitChanged, this, &ArgInspector::updateUnit);
}

} // namespace
