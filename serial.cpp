#include "serial.h"
#include<QDebug>
  #include <QSerialPortInfo>
#include "nmea.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent),
    portName("ttyUSB1"), // Replace with the name of your serial port
    baudRate(115200) // Replace with the baud rate of your serial communication
    ,mlat("null")
    ,mlon("null")
{
    QString usbport;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &portInfo, ports) {
        qDebug() << "Port Name:" << portInfo.portName();
        qDebug() << "Description:" << portInfo.description();
        qDebug() << "Manufacturer:" << portInfo.manufacturer();
        if(portInfo.manufacturer() == "Prolific Technology Inc."){
            usbport=portInfo.portName();
        }
    }
    portName=usbport;
    serialPort = new QSerialPort(this);
    reconnectTimer = new QTimer(this);

    connect(serialPort, &QSerialPort::errorOccurred, this, &SerialManager::handleSerialError);
    connect(serialPort, &QSerialPort::readyRead, this, &SerialManager::readData);
    connect(reconnectTimer, &QTimer::timeout, this, &SerialManager::startReading);
}

SerialManager::~SerialManager()
{
    if (serialPort->isOpen())
        serialPort->close();
}


QString SerialManager::lat(){
    return mlat;
}
QString SerialManager::lon(){
    return mlon;
}

Q_INVOKABLE void SerialManager::startReading()
{
    if (serialPort->isOpen())
        serialPort->close();

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial port opened:" << portName;
    }
    else
    {
        QString usbport;
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        foreach (const QSerialPortInfo &portInfo, ports) {
            qDebug() << "Port Name:" << portInfo.portName();
            qDebug() << "Description:" << portInfo.description();
            qDebug() << "Manufacturer:" << portInfo.manufacturer();
            if(portInfo.manufacturer() == "Prolific Technology Inc."){
                usbport=portInfo.portName();
            }
        }
        portName=usbport;
        qDebug() << "Failed to open serial port:" << portName;
        reconnectTimer->start(5000); // Retry after 5 seconds
    }
}

void SerialManager::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        qDebug() << "Serial port disconnected.";
        reconnectTimer->start(5000); // Retry after 5 seconds
    }
}
QByteArray ba,line;
QString templa,templo;
int i=0;
void SerialManager::readData()
{
    Nmea nm;
    QByteArray newData = serialPort->readAll();
      QString str="kk";
    // Process the received data here
    ba += newData;

    // Process the received data
    int newlineIndex;
    while ((newlineIndex = ba.indexOf('\n')) != -1) {

        //
        line = ba.left(newlineIndex);
        // Handle the line of data here
        qDebug() << "Received line of data:" << line;
        str=QString(line);
        qDebug()<<"str is"<<str;
        nm.parse(str);
        i++;
        qDebug()<<"value of i :"<<QString::number(i);
        if(nm.m_lat!="" && nm.m_lon!=""){
            mlat=nm.m_lat;//+QString::number(i);
            mlon=nm.m_lon;
            templa=mlat;
            templo=mlon;
        }
        else{
            mlat=templa;
            mlon=templo;
        }
        handleCoordinates(mlat.toDouble(),mlon.toDouble());
        //        qDebug()<<"double value from serial "<<temp;
        emit latChanged();
        emit lonChanged();
        qDebug()<<"serial m_lat "<<nm.m_lat<<"serial m_lon"<<nm.m_lon;
        qDebug()<<"serial mlat"<<mlat;
        //        QString filename = "/home/kunal/RealTime_geo/data.buf";
        //        QFile file(filename);
        //        if (!file.open(QIODevice::ReadWrite | QIODevice::ReadWrite))
        //            return;
        //        QTextStream out(&file);
        //        out << QString(line) ;//<< "\n";
        //        //                    out << QString( line ).remove("\r").remove("\n") << "\n";

        ba.remove(0, newlineIndex + 1);
    }
}

void SerialManager::setLat(){

}
void SerialManager::setLon(){

}

