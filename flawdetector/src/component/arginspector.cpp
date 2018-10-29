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

void ArgInspector::focusInEvent(QFocusEvent *)
{
    // show editor
    createEditor();
}

void ArgInspector::focusOutEvent(QFocusEvent *)
{
    // close editor
    closeEditor();
}

void ArgInspector::setFocus()
{
    if(hasFocus())
        clearFocus();
    else
        QWidget::setFocus();
}

} // namespace
