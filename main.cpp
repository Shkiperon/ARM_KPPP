#include <QApplication>
#include <QMessageBox>
#include "qtconntodb.h"
#include "qtrelay.h"
#include "qtoknoapp.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QThread *conn_thread = new QThread;
    qtOknoApp *cOkno = new qtOknoApp;
    cOkno->moveToThread(conn_thread);
    qtrelay *relay = new qtrelay;
    relay->moveToThread(conn_thread);
    connToDB *cConn = new connToDB(0,"172.20.202.75");
    cConn->moveToThread(conn_thread);
    QObject::connect(&app,&QApplication::lastWindowClosed,relay,&qtrelay::stopRelay);
    QObject::connect(relay,&qtrelay::sgnRelayStoped,&app,&QApplication::quit);
    QObject::connect(conn_thread,&QThread::started,cConn,&connToDB::testConn);
    QObject::connect(cConn,&connToDB::sgnSuccessConnTest,cOkno,&qtOknoApp::disableBtnRetryConn);
    QObject::connect(cConn,&connToDB::sgnFailConnTest,cOkno,&qtOknoApp::enableBtnRetryConn);
    QObject::connect(cOkno,&qtOknoApp::sgnBtnRetryConnPressed,cConn,&connToDB::testConn);
    QObject::connect(relay,&qtrelay::sgnRelayEndReadFromUART,cConn,&connToDB::regOnWorkToGTM);
    QObject::connect(cConn,&connToDB::sgnEndZapros,relay,&qtrelay::propuskProcessing);
    QObject::connect(relay,&qtrelay::sgnStartPropuskProcessing,cOkno,&qtOknoApp::updateOkno);
    QObject::connect(relay,&qtrelay::sgnEndPropuskProcessing,cOkno,&qtOknoApp::defaultOkno);
    QObject::connect(relay,&qtrelay::sgnNeedUpdOkno,cOkno,&qtOknoApp::updateOknoLockerOpenedManualy);
    QObject::connect(relay,&qtrelay::sgnNeedDefOkno,cOkno,&qtOknoApp::defaultOkno);
    conn_thread->start();

    cOkno->mainOkno->showFullScreen();

    return app.exec();
}
