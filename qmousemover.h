//Class that emulate mouse moving
#ifndef QMOUSEMOVER_H
#define QMOUSEMOVER_H

#include <QObject>
#include <QWidget>
#include <QTest>
#include <QTimer>

class qMouseMover : public QObject
{
    Q_OBJECT
public:
    explicit qMouseMover(QObject *parent = 0);

signals:

public slots:
    void emulateMove();

private:
    QWidget *widget;

};

#endif // QMOUSEMOVER_H
