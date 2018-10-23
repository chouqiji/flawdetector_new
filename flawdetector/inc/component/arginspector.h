#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QWidget>
#include "component/common.h"
#include "devicearg/viewport.h"

namespace Component
{

class ArgInspector : public QWidget
{
    Q_OBJECT
public:
    explicit ArgInspector(QWidget* parent) : QWidget{parent} {}
    virtual ~ArgInspector() = default;

    using ArgPointer = QSharedPointer<DeviceArg::ViewPort>;
    void bind(ArgPointer pArg, Converter converter = defaultConverter);
    virtual void setEditor(QWidget*) {}
    virtual void activateEditor() {}

protected:
    virtual void setValue(const QString&) {}
    virtual void setName(const QString&) {}
    virtual void setUnit(const QString&) {}

    Converter mConverter;
    ArgPointer mArgPointer;
    QWidget *mEditor;

private:
    void updateValue(const QVariant& val) {setValue(mConverter(val));}
    void updateName(const QString& name) {setName(name);}
    void updateUnit(const QString& unit) {setUnit(unit);}
};

} // namespace

#endif // ARGINSPECTOR_H
