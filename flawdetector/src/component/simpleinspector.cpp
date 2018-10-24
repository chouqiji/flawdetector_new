#include "component/simpleinspector.h"
#include "ui_simpleinspector.h"

namespace Component {

SimpleInspector::SimpleInspector(QWidget *parent) :
    ArgInspector{parent},
    ui(new Ui::SimpleInspector)
{
    ui->setupUi(this);
}

SimpleInspector::~SimpleInspector()
{
    delete ui;
}

void SimpleInspector::activateEditor()
{
    if(mCreator != nullptr)
        mCreator(ui->value)->show();
}

void SimpleInspector::setValue(const QString &value)
{
    ui->value->setText(value);
}

void SimpleInspector::setName(const QString &name)
{
    ui->name->setText(name);
}

void SimpleInspector::setUnit(const QString &unit)
{
    ui->unit->setText(unit);
}

}
