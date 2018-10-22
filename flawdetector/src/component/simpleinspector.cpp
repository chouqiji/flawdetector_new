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

void SimpleInspector::setEditor(QWidget *editor)
{
    mEditor = editor;
    mEditor->setParent(this);
    mEditor->hide();
}

void SimpleInspector::activateEditor()
{
    constexpr int insertPostion = 1;
    ui->value->hide();
    mEditor->show();
    ui->layout->insertWidget(insertPostion, mEditor);
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
