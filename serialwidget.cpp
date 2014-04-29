#include "serialwidget.h"
#include "ui_serialwidget.h"

SerialWidget::SerialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialWidget)
{
    ui->setupUi(this);

    _serial_port = new QSerialPort(this);

    //Initialize baud rate combo box
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud1200));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud2400));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud4800));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud9600));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud19200));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud38400));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud57600));
    ui->baudRateBox->addItem(QString::number(QSerialPort::Baud115200));
    ui->baudRateBox->setCurrentText("9600");
    connect(ui->refreshButton,SIGNAL(clicked()),SLOT(refreshAvailablePorts()));
    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(connectCurrentPort()));
    connect(ui->baudRateBox,SIGNAL(activated(QString)),SLOT(setBaudRate(QString)));
    connect(ui->disconnectButton,SIGNAL(clicked()),SLOT(disconnectPort()));
    connect(_serial_port,SIGNAL(readyRead()),SLOT(receiveData()));
}

SerialWidget::~SerialWidget()
{
    delete ui;
}
void SerialWidget::sendArucoMarkers(vector<aruco::Marker> markers)
{
    if(_serial_port->isOpen()){
        /*for(int i =0;i< markers.size();i++){
            QString marker_string;
            char nl = '\n';
            //marker_string.append(QString::number(markers[i].id));
            //marker_string.append(nl);
        }*/
        _serial_port->write(QString("Marker Found").toUtf8());
    }
}

void SerialWidget::connectPort(QString port_name)
{
    _serial_port->close();
    _serial_port->setPortName(port_name);
    _serial_port->open(QIODevice::ReadWrite);
    _serial_port->setBaudRate(ui->baudRateBox->currentText().toInt());
    _serial_port->setParity(QSerialPort::NoParity);
    _serial_port->setDataBits(QSerialPort::Data8);
    _serial_port->setStopBits(QSerialPort::OneStop);
}
void SerialWidget::connectCurrentPort()
{
    _serial_port->close();
    _serial_port->setPortName(ui->availablePortsBox->currentText());
    _serial_port->open(QIODevice::ReadWrite);
    _serial_port->setBaudRate(ui->baudRateBox->currentText().toInt());
    _serial_port->setParity(QSerialPort::NoParity);
    _serial_port->setDataBits(QSerialPort::Data8);
    _serial_port->setStopBits(QSerialPort::OneStop);
}

void SerialWidget::disconnectPort() {
    _serial_port->close();
}

void SerialWidget::setBaudRate(QString baud_rate)
{
    if(_serial_port->isOpen())
        _serial_port->setBaudRate(baud_rate.toInt());
}

void SerialWidget::refreshAvailablePorts()
{
    ui->availablePortsBox->clear();
    QList<QSerialPortInfo> available_ports = QSerialPortInfo::availablePorts();
    for(int i = 0; i < available_ports.size(); i++){
        ui->availablePortsBox->addItem(available_ports.at(i).portName());
    }
}
void SerialWidget::receiveData()
{
    //_current_data = _serial_port->readAll();
    ui->receivedDataBox->append(_serial_port->readAll());
    //ui->receivedDataBox->setText(_received_data);

    //ui->receivedDataBox->append();
}

void SerialWidget::clearReceivedData()
{
    ui->receivedDataBox->clear();
}

void SerialWidget::saveReceivedData()
{

}
