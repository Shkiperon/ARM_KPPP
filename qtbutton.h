//Class that checking in runtime button status (pressed/released)
#ifndef QTBUTTON_H
#define QTBUTTON_H

#include <QObject>
#include <wiringPi.h>

#define PIN18 1 //wiringPi 1 (GPIO 18)
#define RELAY_RFID 1
#define RELAY_LOCKER 3
#define RELAY_BUZZER 4

class qtbutton : public QObject
{
    Q_OBJECT
public:
    explicit qtbutton(QObject *parent = 0);

signals:
    void sgnNeedSwitchRelayON(int);
    void sgnNeedSwitchRelayOFF(int);
    void sgnBtnPressed();
    void sgnBtnUnPressed();

public slots:
    void buttonProcessing();
};

#endif // QTBUTTON_H
