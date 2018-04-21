#include "qtrelay.h"

qtrelay::qtrelay(QObject *parent) : QObject(parent)
{
    if (wiringPiSetup() == -1)
    {
      QMessageBox::information(0,"WiringPi error","Could not execute wiringPiSetup() procedure");
      emit sgnWiringPiErr();
    }
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);

    pinMode(PIN14,INPUT); //GPIO 14, that using for checking that reader is connected

    if(digitalRead(PIN14))
    {
        uart_thread = new QThread();
        uart = new qtRFID();
        uart->moveToThread(uart_thread);
        connect(uart_thread,&QThread::started,uart,&qtRFID::uartProcessing);
        connect(uart,&qtRFID::endReadFromUART,this,&qtrelay::slotEmitEndReadFromUART);
        uart_thread->start();
        btn_thread = new QThread();
        btn = new qtbutton();
        btn->moveToThread(btn_thread);
        connect(btn_thread,&QThread::started,btn,&qtbutton::buttonProcessing);
        connect(btn,&qtbutton::sgnNeedSwitchRelayON,this,&qtrelay::switchRelayON);
        connect(btn,&qtbutton::sgnNeedSwitchRelayOFF,this,&qtrelay::switchRelayOFF);
        connect(btn,&qtbutton::sgnBtnPressed,this,&qtrelay::emitNeedUpdOkno);
        connect(btn,&qtbutton::sgnBtnUnPressed,this,&qtrelay::emitNeedDefOkno);
        btn_thread->start();
        mover_thread = new QThread();
        mover = new qMouseMover();
        mover->moveToThread(mover_thread);
        QObject::connect(mover_thread,&QThread::started,mover,&qMouseMover::emulateMove);
        mover_thread->start();
    }
    else
    {
        stopRelay();
        QMessageBox::information(0,"RFID reader","Device not found. Check connection and restart the program.");
    }

}

void qtrelay::stopRelay()
{
    switchALLRelayOFF();
    emit sgnRelayStoped();
}

void qtrelay::emitNeedUpdOkno()
{
    emit sgnNeedUpdOkno();
}

void qtrelay::emitNeedDefOkno()
{
    emit sgnNeedDefOkno();
}

void qtrelay::switchRelayON(int relayNum)
{
    switch(relayNum)
    {
        case 1:
            digitalWrite(IN1,0);
            break;
        case 2:
            digitalWrite(IN2,0);
            break;
        case 3:
            digitalWrite(IN3,0);
            break;
        case 4:
            digitalWrite(IN4,0);
            break;
        default:
            //qDebug()<<"Incorrect relay number: "<<relayNum;
            break;
    }
}

void qtrelay::switchRelayOFF(int relayNum)
{
	switch(relayNum)
	{
        case 1:
            digitalWrite(IN1,1);
            break;
        case 2:
            digitalWrite(IN2,1);
            break;
        case 3:
            digitalWrite(IN3,1);
            break;
        case 4:
            digitalWrite(IN4,1);
            break;
		default:
            //qDebug()<<"Incorrect relay number: "<<relayNum;
            break;
	}
}

void qtrelay::switchALLRelayON()
{
	digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
}

void qtrelay::switchALLRelayOFF()
{
	digitalWrite(IN1,1);
    digitalWrite(IN2,1);
    digitalWrite(IN3,1);
    digitalWrite(IN4,1);
}

void qtrelay::slotEmitEndReadFromUART(QString data)
{
    switchRelayON(1);
    emit sgnRelayEndReadFromUART(data);
}

void qtrelay::propuskProcessing(QString data)
{
    emit sgnStartPropuskProcessing(data);
    QStringList newdata = data.split("|");
    if(newdata.at(0)=="+")
    {
        switchRelayON(1);
        switchRelayOFF(2);
        switchRelayON(4);
        delay(10000);
        switchRelayOFF(1);
        switchRelayON(2);
        switchRelayOFF(4);
    }
    else
    {
        switchRelayON(1);
        switchRelayON(2);
        switchRelayOFF(4);
        delay(10000);
        switchRelayOFF(1);
    }
    emit sgnEndPropuskProcessing();
}
