//Control class for 4-relay module
#ifndef QTRELAY_H
#define QTRELAY_H

#include <QObject>
#include <QThread>
#include <wiringPi.h>
#include "qtrfid.h"
#include "qtbutton.h"
#include "qmousemover.h"

#define IN1 0 //wiring Pi 0 (GPIO 17) -> OFF (RFID power circuit)
#define IN2 7 //wiring Pi 7 (GPIO 4) -> ON (button power circuit)
#define IN3 9 //wiring Pi 9 (GPIO 3) -> ON (electromagnetic lock power circuit)
#define IN4 8 //wiring Pi 8 (GPIO 2) -> OFF
#define PIN14 15 //wirin Pi 15 (GPIO 14) -> LED of RFID reader

class qtrelay : public QObject
{
    Q_OBJECT
public:
    explicit qtrelay(QObject *parent = 0);

signals:
    void sgnWiringPiErr(); //Signal of errors of work WiringPi library
    void sgnRelayStoped();
    void sgnRelayEndReadFromUART(QString);
    void sgnStartPropuskProcessing(QString);
    void sgnEndPropuskProcessing();
    void sgnNeedUpdOkno();
    void sgnNeedDefOkno();

public slots:
    void switchRelayON(int pinNum);
    void switchRelayOFF(int pinNum);
    void switchALLRelayON();
    void switchALLRelayOFF();
    void slotEmitEndReadFromUART(QString);
    void stopRelay();
    void propuskProcessing(QString);
    void emitNeedUpdOkno();
    void emitNeedDefOkno();

private:
    qtRFID *uart;
    QThread *uart_thread;
    qtbutton *btn;
    QThread *btn_thread;
    qMouseMover *mover;
    QThread *mover_thread;
};

#endif // QTRELAY_H
