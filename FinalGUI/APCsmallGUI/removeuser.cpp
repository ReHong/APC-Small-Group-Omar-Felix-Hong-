#include "removeuser.h"
#include "ui_removeuser.h"

removeuser::removeuser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::removeuser)
{
    ui->setupUi(this);
}

removeuser::~removeuser()
{
    delete ui;
}
