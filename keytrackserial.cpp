#include "keytrackserial.h"
#include "ui_keytrackserial.h"

KeytrackSerial::KeytrackSerial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeytrackSerial)
{
    ui->setupUi(this);
    _serial_port = new QSerialPort(this);

    refreshPortList();

    //Populate baudRate combo box with baud rate options
    ui->baudRate->addItem(QString::number(QSerialPort::Baud1200));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud2400));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud4800));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud9600));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud19200));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud38400));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud57600));
    ui->baudRate->addItem(QString::number(QSerialPort::Baud115200));
    //Preset baud rate selection to 9600
    ui->baudRate->setCurrentText(QString::number(QSerialPort::Baud9600));

    //Populate parity combo box with parity options
    ui->parity->addItem("No Parity");
    ui->parity->addItem("Even Parity");
    ui->parity->addItem("Odd Parity");
    ui->parity->addItem("Space Parity");
    ui->parity->addItem("Mark Parity");

    updatePortSettings();

    connect(ui->connectButton,SIGNAL(clicked()),SLOT(connectPort()));
    connect(ui->disconnectButton, SIGNAL(clicked()),SLOT(disconnectPort()));
    connect(ui->baudRate,SIGNAL(currentTextChanged(QString)),SLOT(updatePortSettings()));
    connect(ui->parity,SIGNAL(currentTextChanged(QString)), SLOT(updatePortSettings()));
    connect(ui->dataBits,SIGNAL(currentTextChanged(QString)),SLOT(updatePortSettings()));
    connect(ui->stopBits,SIGNAL(currentTextChanged(QString)),SLOT(updatePortSettings()));
    connect(_serial_port, SIGNAL(readyRead()),SLOT(handleReadyRead()));
    connect(ui->sendButton,SIGNAL(clicked()),SLOT(sendTextFromBox()));
    connect(ui->sendBox,SIGNAL(returnPressed()),SLOT(sendTextFromBox()));
    connect(this,SIGNAL(destroyed()),SLOT(disconnectPort()));
}

KeytrackSerial::~KeytrackSerial()
{
    _serial_port->close();
    delete ui;
}

void KeytrackSerial::refreshPortList()
{
    //Clear the combo box
    ui->portList->clear();

    //Populate the combo box with the available ports
    QList<QSerialPortInfo> available_ports = QSerialPortInfo::availablePorts();
    for(int i=0; i < available_ports.size();i++) {
        ui->portList->addItem(available_ports.at(i).portName());
    }
}

void KeytrackSerial::updatePortSettings()
{
    //Update baud rate settings
    _serial_port->setBaudRate(ui->baudRate->currentText().toInt());

    //Update parity settings
    if(ui->parity->currentText() == QString("No Parity"))
        _serial_port->setParity(QSerialPort::NoParity);
    else if(ui->parity->currentText() == QString("Even Parity"))
        _serial_port->setParity(QSerialPort::EvenParity);
    else if(ui->parity->currentText() == QString("Odd Parity"))
        _serial_port->setParity(QSerialPort::OddParity);
    else if(ui->parity->currentText() == QString("Space Parity"))
        _serial_port->setParity(QSerialPort::SpaceParity);
    else if(ui->parity->currentText() == QString("Mark Parity"))
        _serial_port->setParity(QSerialPort::MarkParity);
    else
        _serial_port->setParity(QSerialPort::NoParity);

    _serial_port->setDataBits(QSerialPort::Data8);
    _serial_port->setStopBits(QSerialPort::OneStop);
}

void KeytrackSerial::sendTextFromBox()
{
    sendText(ui->sendBox->text());
    ui->sendBox->clear();
}

void KeytrackSerial::sendText(QString text) {
    _serial_port->write(text.toUtf8());
    _sent_data.append(text.toUtf8());
    ui->sentBox->setText(QString(_sent_data));
}

void KeytrackSerial::handleReadyRead()
{
    _received_data.append(_serial_port->readAll());
    ui->receivedBox->setText(QString(_received_data));

    //Scroll to bottom
    QTextCursor c = ui->receivedBox->textCursor();
    c.movePosition(QTextCursor::End);
    ui->receivedBox->setTextCursor(c);
}

void KeytrackSerial::connectPort()
{
    _serial_port->setPortName(ui->portList->currentText());
    _serial_port->open(QIODevice::ReadWrite);
}

void KeytrackSerial::disconnectPort()
{
    _serial_port->close();
}
