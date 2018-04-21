#include "qtconntodb.h"

connToDB::connToDB(QObject *parent) :
    QObject(parent)
{
}

connToDB::connToDB(QObject *parent,QString clientIp) :
    QObject(parent)
{
    ip=clientIp;
}

connToDB::connToDB(QObject *parent,QString clientIp, int16_t clientPort) :
    QObject(parent)
{
    ip=clientIp;
    port=clientPort;
}

QByteArray connToDB::strTo866(QString targetString)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    QByteArray encodedString = codec->fromUnicode(targetString);
    return encodedString;
}

QString connToDB::strToUnicode(QByteArray targetString)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    QString encodedString = codec->toUnicode(targetString);
    return encodedString;
}

quint8 connToDB::openConnToGTM()
{
    quint8 status = 2;
    sock = new QTcpSocket(this);
    sock->connectToHost(ip,port);
    if(sock->waitForConnected(3000))
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

void connToDB::closeConnToGTM()
{
    sock->close();
}

void connToDB::testConn()
{
    if(openConnToGTM())
    {
        closeConnToGTM();
        emit sgnSuccessConnTest();
    }
    else
    {
        closeConnToGTM();
        emit sgnFailConnTest();
    }
}

void connToDB::testToGTM()
{
    otvetGTM = "";
    otvetGTM=zaprosToGTM(strTestGTM);
    qDebug() << "!" + otvetGTM;
}

void connToDB::regOnWorkToGTM(QString rfidNumber)
{
    otvetGTM = "";
    otvetGTM=zaprosToGTM("D|REGTOWRK^SHKIP(\""+rfidNumber+"\")");
    qDebug() << otvetGTM;
}

QString connToDB::zaprosToGTM(QString zaprosstr)
{
    otvetGTM="-|";
    if (openConnToGTM())
    {
        sock->write(strTo866(zaprosstr+strEndGTM));
        sock->waitForBytesWritten(1000);
        sock->waitForReadyRead(5000);
        int answerNumBytes = sock->bytesAvailable();
        QByteArray answerArray = sock->readAll();
        if(answerArray.at(--answerNumBytes)==endSymbol)
        {
            answerArray.chop(1);
            otvetGTM=strToUnicode(answerArray);
        }
        else
        {
            otvetGTM=strToUnicode(answerArray);
        }
        sock->close();
        emit sgnEndZapros(otvetGTM);
        return otvetGTM;
    }
    else
    {
        otvetGTM=otvetGTM+"Could not connect to database!";
        sock->close();
        emit sgnEndZapros(otvetGTM);
        return otvetGTM;
    }
}
