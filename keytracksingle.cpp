#include "keytracksingle.h"
#include "ui_keytracksingle.h"

KeytrackSingle::KeytrackSingle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeytrackSingle)
{
    ui->setupUi(this);
}

KeytrackSingle::~KeytrackSingle()
{
    delete ui;
}
