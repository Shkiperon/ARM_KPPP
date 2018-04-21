//Connection class to MUMPS DB (GTM)
#ifndef QTCONNTODB
#define QTCONNTODB

#include <QObject>
#include <QTextCodec>
#include <QTcpSocket>
#include <QAbstractSocket>

class connToDB : public QObject
{
    Q_OBJECT
public:
    explicit connToDB(QObject *parent);
    explicit connToDB(QObject *parent, QString clientIp);
    explicit connToDB(QObject *parent, QString clientIp, int16_t clientPort);
signals:
    void sgnEndZapros(QString strOtvet);
    void sgnFailConnTest();
    void sgnSuccessConnTest();
public slots:
    void testConn();
    void testToGTM();
    void regOnWorkToGTM(QString rfidNumber);

private:
    QTcpSocket *sock;
    QString ip = "127.0.0.1";
    int16_t port = 6321;
    QString strEndGTM="\r";
    QString strTestGTM="!";
    QString otvetGTM="";
    QChar endSymbol = QChar(0x03);
    quint8 openConnToGTM();
    void closeConnToGTM();
    QByteArray strTo866(QString targetString);
    QString strToUnicode(QByteArray targetString);
    QString zaprosToGTM(QString zaprosstr);
};

#endif // QTCONNTODB

