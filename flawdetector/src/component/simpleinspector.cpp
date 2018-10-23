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
    // FIXME: multiple call of this function will cause memory leakage
    mEditor = editor;
    mEditor->setParent(ui->value);
    auto p = new QBoxLayout(QBoxLayout::LeftToRight, ui->value);
    p->addWidget(mEditor);
    p->setContentsMargins(0, 0, 0, 0);
}

void SimpleInspector::activateEditor()
{
    mEditor->show();
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
