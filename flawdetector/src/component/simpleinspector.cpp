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

void SimpleInspector::createEditor()
{
    if(mCreator != nullptr)
    {
        mEditor = mCreator(ui->value);
        mEditor->show();
        connect(mEditor, &QWidget::destroyed, this, &QWidget::clearFocus);
    }
}

void SimpleInspector::closeEditor()
{
    if(mEditor != nullptr)
    {
        mEditor->close();
    }
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
