#include "qtrfid.h"

QString UART_DEVICE = "/dev/ttyAMA0";
char START_FLAG = '\x02';
char END_FLAG = '\x03';

qtRFID::qtRFID(QObject *parent) : QObject(parent)
{
    if ((dev = serialOpen (UART_DEVICE.toStdString().c_str(),9600))< 0)
    {
        QMessageBox::information(0,"UART error","Unable to open serial device: "+UART_DEVICE+"("+QString::number(dev)+")");
        emit sgnErrStartUART();
    }
    emit sgnStartUART();
}

qtRFID::~qtRFID()
{
    serialClose(dev);
    delete &dev;
    delete &strFromDev;
    emit sgnFinUART();
}

QString qtRFID::getStrFromDev()
{
    return strFromDev;
}

QString qtRFID::strToUnicode(QByteArray targetString)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    QString encodedString = codec->toUnicode(targetString);
    return encodedString;
}

void qtRFID::uartProcessing()
{
    int i=0,j=0;
    bool ok = false;
    QByteArray arrFromDev;
    QString tmp;
    arrFromDev.resize(16);
    unsigned short checksum;
    while(1)
    {
        delay (50) ;
        arrFromDev.clear();
        strFromDev="";
        checksum=0;
        i=-1;
        while(serialDataAvail(dev))
        {
            ++i;
            arrFromDev[i]= serialGetchar(dev);
            qDebug() << arrFromDev.data();
            if(arrFromDev.at(i)==START_FLAG)
            {
				i=0;
				arrFromDev.clear();
				arrFromDev[i]=START_FLAG;
			}
            if(arrFromDev.at(0)==START_FLAG && arrFromDev.at(i)==END_FLAG)
            {
                j=0;
                for(i=0;i<=5;i++)
                {
                    j++;
                    tmp = strToUnicode(arrFromDev.mid(j,2));
                    checksum ^= tmp.toUInt(&ok,16);
                    j++;
                }
                if (checksum==0)
                {
                    //qDebug() << "Check: " << checksum;
                    strFromDev = strToUnicode(arrFromDev.mid(1,10));
                    //qDebug() << strFromDev;
                    emit endReadFromUART(strFromDev);
                }
            }
        }
    }
}

void qtRFID::uart_Error()
{
    QString str = QString::number(dev);
    QMessageBox::information(0,"UART error","Error while working with UART "+str);
    serialClose(dev);
}
