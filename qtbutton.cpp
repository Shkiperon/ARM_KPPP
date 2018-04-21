#include "qtbutton.h"

qtbutton::qtbutton(QObject *parent) :
    QObject(parent)
{
    pinMode(PIN18,INPUT);
    pullUpDnControl(PIN18,PUD_UP);
}

void qtbutton::buttonProcessing()
{
    while(1)
    {
        delay (250) ;
        if(!digitalRead(PIN18))
        {
            while(!digitalRead(PIN18))
            {
                delay (100);
                emit sgnBtnPressed();
                emit sgnNeedSwitchRelayON(1);
                emit sgnNeedSwitchRelayOFF(3);
                emit sgnNeedSwitchRelayON(4);
            }
            emit sgnNeedSwitchRelayOFF(1);
            emit sgnNeedSwitchRelayON(3);
            emit sgnNeedSwitchRelayOFF(4);
            emit sgnBtnUnPressed();
        }
    }
}
