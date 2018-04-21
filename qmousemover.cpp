#include "qmousemover.h"

qMouseMover::qMouseMover(QObject *parent) :
    QObject(parent)
{
    widget = new QWidget;
    widget->setCursor(Qt::BlankCursor);
}

void qMouseMover::emulateMove()
{
    while(true)
    {
        QTest::mouseMove(widget,QPoint(0,1),6000);
        QTest::mouseMove(widget,QPoint(0,0),-1);
    }
}

/*void qMouseMover::emulatePressKey()
{
    while(true)
    {
        QTest::keyClick(widget,'w',Qt::NoModifier,6000);
        qDebug()<<"Pressing the w button";
    }
}
*/
