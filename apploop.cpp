#include "apploop.h"
#include "dbconnection.h"
#include "activereading.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVectorIterator>

AppLoop::AppLoop(QObject *parent) : QObject(parent) { }

void AppLoop::run()
{
    QFile file("appconfig");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        qDebug() << "ERROR - shutting down - app config not found or unreadable";
        exit(1);
    }

    QTextStream in(&file);
    username_ = in.readLine();

    file.close();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AppLoop::updateActiveReadings);
    timer->setSingleShot(true);
    timer->singleShot(10, this, &AppLoop::updateActiveReadings);
    timer->setSingleShot(false);
    timer->start(900000);
}

void AppLoop::updateActiveReadings()
{
    QFile file("/etc/hostname");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        qDebug() << "ERROR - shutting down - hostname not found or unreadable";
        exit(1);
    }

    QTextStream in(&file);
    QString hostname = in.readLine();

    file.close();

    QSqlDatabase db = DbConnection::getInstance().db();

    if (db.open())
    {
        QSqlQuery query(db);
        query.exec("SELECT * FROM \"Devices\" WHERE \"Hostname\" = '" + hostname + "' AND \"UserId\" = '" + username_ + "'");
        while (query.next())
        {
            QString qDeviceId = query.value(0).toString();
            query.exec("SELECT * FROM \"ActiveReadings\" WHERE \"DeviceId\" = '" + qDeviceId + "'");
            while (query.next())
            {
                QVectorIterator<ActiveReading*> it(activeReadings_);
                while(it.hasNext())
                {
                    ActiveReading *ar = it.next();
                    delete ar;
                }

                activeReadings_.clear();
                QString qActiveReadingDeviceId = query.value(3).toString();
                if(qDeviceId == qActiveReadingDeviceId)
                {
                    ActiveReading *activeReading = new ActiveReading(
                                query.value(0).toString(),
                                query.value(2).toString(),
                                query.value(3).toString(),
                                query.value(4).toString(),
                                query.value(5).toString(),
                                query.value(6).toString());

                    activeReadings_.push_back(activeReading);
                }
            }

        }
    }
    else qDebug() << db.lastError();
}
