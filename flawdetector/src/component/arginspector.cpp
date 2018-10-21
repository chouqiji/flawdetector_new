#include "component/arginspector.h"

namespace Component {

void ArgInspector::bind(ArgInspector::ArgPointer pArg, Converter converter)
{
    mArgPointer = pArg;
    mConverter = converter;

    updateName(mArgPointer->displayedName());
    updateUnit(mArgPointer->displayedUnit());
    updateValue(mArgPointer->value());

    mArgPointer->connect(&DeviceArg::Signals::valueChanged, this, &ArgInspector::updateValue);
    mArgPointer->connect(&DeviceArg::Signals::nameChanged, this, &ArgInspector::updateName);
    mArgPointer->connect(&DeviceArg::Signals::unitChanged, this, &ArgInspector::updateUnit);
}

} // namespace
