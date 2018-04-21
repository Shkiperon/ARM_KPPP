#include "qtoknoapp.h"

qtOknoApp::qtOknoApp(QObject *parent) : QObject(parent)
{
    mainOkno = new QWidget();
    layerVert = new QVBoxLayout();
    layerDown = new QHBoxLayout();
    lblUp = new QLabel();
    lblCenter = new QLabel();
    lblDown = new QLabel();
    btnRetryConn = new QPushButton();

    connect(btnRetryConn,&QPushButton::clicked,this,&qtOknoApp::emitBtnRetryConnPressed);

    defaultOkno();
    btnRetryConn->setText("Retry connection");
    disableBtnRetryConn();

    layerDown->addWidget(btnRetryConn);
    layerDown->addWidget(lblDown);

    layerVert->addWidget(lblUp);
    layerVert->addWidget(lblCenter);
    layerVert->addLayout(layerDown);

    mainOkno->setLayout(layerVert);
}

qtOknoApp::~qtOknoApp()
{
    delete mainOkno;
    delete lblUp;
    delete lblCenter;
    delete lblDown;
    delete btnRetryConn;
    delete layerVert;
    delete layerDown;
    delete &strHelloCenter;
}

void qtOknoApp::updateOkno(QString str)
{
    lblCenter->setText("<h2><center>"+str+"</center></h2>");
}
void qtOknoApp::defaultOkno()
{
    lblCenter->setText("<h1><center>"+strHelloCenter+"</center></h1>");
}

void qtOknoApp::enableBtnRetryConn()
{
    btnRetryConn->setEnabled(true);
    btnRetryConn->setVisible(true);
}

void qtOknoApp::disableBtnRetryConn()
{
    btnRetryConn->setDisabled(true);
    btnRetryConn->setVisible(false);
}

void qtOknoApp::emitBtnRetryConnPressed()
{
    emit sgnBtnRetryConnPressed();
}

void qtOknoApp::updateOknoLockerOpenedManualy()
{
    updateOkno("Lock is opened manually. Reader turned off.");
}
