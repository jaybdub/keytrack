//View to connect serial port, and send data

#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <aruco/aruco.h>
#include <vector>

namespace Ui {
class SerialWidget;
}

class SerialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialWidget(QWidget *parent = 0);
    ~SerialWidget();
public slots:
    void refreshAvailablePorts();
    void connectPort(QString port_name);
    void disconnectPort();
    void setBaudRate(QString baud_rate);
    void sendArucoMarkers(vector<aruco::Marker> markers);
private slots:
    void connectCurrentPort();
    void receiveData();
    void clearReceivedData();
    void saveReceivedData();
private:
    bool _autoscroll_enabled;
    QSerialPort* _serial_port;
    Ui::SerialWidget *ui;
};

#endif // SERIALWIDGET_H
