#include "bluetoothwidget.h"
#include "ui_bluetoothwidget.h"

BluetoothWidget::BluetoothWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothWidget)
{
    ui->setupUi(this);
}

BluetoothWidget::~BluetoothWidget()
{
    delete ui;
}
