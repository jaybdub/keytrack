#ifndef KEYTRACKSERIAL_H
#define KEYTRACKSERIAL_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QByteArray>
#include <QTimer>
#include <QTextStream>

namespace Ui {
class KeytrackSerial;
}

class KeytrackSerial : public QWidget
{
    Q_OBJECT

public:
    explicit KeytrackSerial(QWidget *parent = 0);
    ~KeytrackSerial();
public slots:
    void refreshPortList();
    void sendText(QString text);
private slots:
    void updatePortSettings();
    void sendTextFromBox();
    void handleReadyRead();
    void connectPort();
    void disconnectPort();
    //void saveSentDataToFile();
    //void saveReceivedDataToFile();
private:

    QSerialPort *_serial_port;
    QByteArray _received_data;
    QByteArray _sent_data;
    Ui::KeytrackSerial *ui;
};

#endif // KEYTRACKSERIAL_H
