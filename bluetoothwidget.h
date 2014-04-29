#ifndef BLUETOOTHWIDGET_H
#define BLUETOOTHWIDGET_H

#include <QWidget>

namespace Ui {
class BluetoothWidget;
}

class BluetoothWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothWidget(QWidget *parent = 0);
    ~BluetoothWidget();

private:
    Ui::BluetoothWidget *ui;
};

#endif // BLUETOOTHWIDGET_H
