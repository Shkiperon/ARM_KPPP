//Class that updating info on main screen
#ifndef QTOKNOAPP_H
#define QTOKNOAPP_H

#include <QObject>
#include <QThread>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class qtOknoApp : public QObject
{
    Q_OBJECT
public:
    explicit qtOknoApp(QObject *parent = 0);
    ~qtOknoApp();
    QWidget *mainOkno;
    QLabel *lblUp;
    QLabel *lblCenter;
    QLabel *lblDown;
    QPushButton *btnRetryConn;

signals:
	void closeOkno();
    void sgnBtnRetryConnPressed();

public slots:
    void defaultOkno();
    void updateOkno(QString);
    void enableBtnRetryConn();
    void disableBtnRetryConn();
    void emitBtnRetryConnPressed();
    void updateOknoLockerOpenedManualy();

private:
    QVBoxLayout *layerVert;
    QHBoxLayout *layerDown;
    QString strHelloCenter = "Time tracking system of<br>\"Roga i Kopita\" Ltd.<br>welcomes you";

};

#endif // QTOKNOAPP_H
