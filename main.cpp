#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSerialPort>
#include <iostream>
using namespace std;

enum class State {
    WaitingForBoxCode,
    WaitingForQuantite,
    WaitingForClosing,
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    employes e;
    QSerialPort serial;
        serial.setPortName("COM5");
        serial.setBaudRate(QSerialPort::Baud9600);
        if (serial.open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port opened successfully.";

        State currentState = State::WaitingForBoxCode;
        QByteArray boxCode;
        QByteArray quantit;
        QByteArray close;
        Bijou b ;
        QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
            QByteArray data = serial.readAll();

            switch (currentState) {
            case State::WaitingForBoxCode:
                boxCode += data;
                if (boxCode.length() == 3) {
                    qDebug() << "Box code: " << boxCode;
                    if (b.boxExists(boxCode.toInt())) {
                        qDebug() << "TRUE";
                        QString command="b%255";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForQuantite;
                    } else {
                        qDebug() << "FALSE";
                        QString command="r%255";
                        serial.write(command.toStdString().c_str());
                        boxCode.clear();
                    }
                }
                break;

            case State::WaitingForQuantite:
                quantit += data;
                if (quantit.endsWith("*")) {
                    quantit.chop(1);
                    qDebug() << "Quantite: " << quantit;
                    if (b.quantite(quantit.toInt() , boxCode.toInt())) {
                        qDebug() << "Valid quantite and box code"<<boxCode;
                        QString command="g%255";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForClosing;
                    } else {
                        currentState = State::WaitingForBoxCode;
                        qDebug() << "Invalid quantite !!!";
                        QString command="r%255";
                        serial.write(command.toStdString().c_str());
                    }


                    boxCode.clear();
                    quantit.clear();
                }
                break;

            case State::WaitingForClosing:
                close+=data;
                if(close.endsWith("*")){
                    close.chop(1);
                    qDebug()<<"close  :  "<<close;
                    if(close=="CAB"){
                        qDebug() << "Closing the Box";
                        QString command="c";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForBoxCode;
                    }
                    else{
                        qDebug() << "Box still open !!!";
                    }
                    close.clear();
                }
                break;
            default:
                break;
            }
        });
        }
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
