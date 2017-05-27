#ifndef APPLOOP_H
#define APPLOOP_H

#include "activereading.h"
#include <QVector>
#include <QObject>

class AppLoop : public QObject
{
    Q_OBJECT

private:
    QString username_;
    QString hostname_;
    QVector<ActiveReading*> activeReadings_;

public:
    explicit AppLoop(QObject *parent = 0);
    void run();

public slots:
    void updateActiveReadings();

};

#endif // APPLOOP_H
