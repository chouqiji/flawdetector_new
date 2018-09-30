#include "desktop.h"
#include "globalmanager.h"

Desktop::Desktop(QWidget *parent)
    : QMainWindow(parent)
{
    GlobalManager::instance();
}

Desktop::~Desktop()
{

}
