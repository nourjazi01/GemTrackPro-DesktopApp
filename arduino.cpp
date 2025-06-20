#include "arduino.h"

arduino::arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort * arduino::getserial()
{return serial;}

int arduino::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            return 0;
        } else {
            qDebug() << "Failed to open serial port!";
            serial->close(); // Close the port if it fails to open
            return 1;
        }
    }

    return -1;
}


int arduino::close_arduino()
{
    if(serial->isOpen())
    {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray arduino::read_from_arduino()
{
    if (serial->isReadable())
    {
        data = serial->readAll();
        return data;
    }
    else
    {
        // Return an empty QByteArray or handle the error appropriately
        return QByteArray();
    }
}
int arduino::write_to_arduino(QByteArray d)
{
    if (serial->isWritable())
    {
        serial->write(d);
        return 0;  // Return 0 or a suitable success code
    }
    else
    {
        qDebug() << "Couldn't write to serial in the write function";
        return -1;  // Return -1 or a suitable error code
    }
}
