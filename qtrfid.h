//Class for using RDM6300 that connected to Raspberry Pi on GPIO 15

#ifndef QTRFID_H
#define QTRFID_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <wiringPi.h>
#include <wiringSerial.h>

class qtRFID : public QObject
{
    Q_OBJECT
public:
    explicit qtRFID(QObject *parent = 0);
    ~qtRFID();
    QString getStrFromDev();
    QString strToUnicode(QByteArray targetString);

signals:
    void sgnFinUART(); //Shutdown of the class
    void endReadFromUART(QString data); //Output of recieved data
    void sgnStartUART(); //Beginning of the class
    void sgnErrStartUART(); //Error while trying start UART process

public slots:
    void uartProcessing(); //Main
    void uart_Error();//Slot of processing UART errors

private:
    int dev; //UART-connection of RFID-reader
    QString strFromDev;
};

#endif // QTRFID_H
