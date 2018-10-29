#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QFrame>
#include "component/common.h"
#include "devicearg/viewport.h"

namespace Component
{

class ArgInspector : public QFrame
{
    Q_OBJECT
public:
    explicit ArgInspector(QWidget* parent) : QFrame{parent} {}
    virtual ~ArgInspector() override = default;

    using ArgPointer = QSharedPointer<DeviceArg::ViewPort>;
    void bind(ArgPointer pArg, EditorCreator creator = nullptr, Converter converter = defaultConverter);
    void setFocus();

protected:
    virtual void setValue(const QString&) {}
    virtual void setName(const QString&) {}
    virtual void setUnit(const QString&) {}
    virtual void focusInEvent(QFocusEvent *) override;
    virtual void focusOutEvent(QFocusEvent *) override;

    virtual void createEditor() {}
    virtual void closeEditor() {}

    Converter mConverter;
    ArgPointer mArgPointer;
    EditorCreator mCreator = nullptr;

private:
    void updateValue(const QVariant& val) {setValue(mConverter(val));}
    void updateName(const QString& name) {setName(name);}
    void updateUnit(const QString& unit) {setUnit(unit);}
};

} // namespace

#endif // ARGINSPECTOR_H
