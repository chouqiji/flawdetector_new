#ifndef ARGINSPECTOR_H
#define ARGINSPECTOR_H

#include <QWidget>
#include <QVariant>
#include <functional>
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
    using Converter  = std::function<QString(const QVariant&)>;
    virtual void bind(ArgPointer pArg, Converter converter = defaultConverter);
    void setEditor(QWidget *editor) {mEditor = editor;}
    void activateEditor() {mEditor->show();}

protected:
    virtual void setValue(const QString&) {}
    virtual void setName(const QString&) {}
    virtual void setUnit(const QString&) {}


    static QString defaultConverter(const QVariant& in) {return in.toString();}

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
