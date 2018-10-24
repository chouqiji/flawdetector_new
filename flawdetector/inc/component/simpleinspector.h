#ifndef SIMPLEINSPECTOR_H
#define SIMPLEINSPECTOR_H

#include <QWidget>
#include <component/arginspector.h>

namespace Ui {
class SimpleInspector;
}

namespace Component {

class SimpleInspector : public ArgInspector
{
    Q_OBJECT

public:
    explicit SimpleInspector(QWidget *parent = nullptr);
    ~SimpleInspector() override;

    virtual void activateEditor() override;

protected:
    virtual void setValue(const QString& value) override;
    virtual void setName(const QString& name) override;
    virtual void setUnit(const QString& unit) override;

private:
    Ui::SimpleInspector *ui;
};

}

#endif // SIMPLEINSPECTOR_H
