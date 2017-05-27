#include "apploop.h"
#include "dbconnection.h"
#include "activereading.h"
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVectorIterator>

AppLoop::AppLoop(QObject *parent) : QObject(parent)
{
    QFile fileapp("appconfig");
    if(!fileapp.open(QIODevice::ReadOnly))
    {
        qDebug() << fileapp.errorString();
        qDebug() << "ERROR - shutting down - app config not found or unreadable";
        exit(1);
    }

    QTextStream inapp(&fileapp);
    username_ = inapp.readLine();

    fileapp.close();

    QFile fileh("/etc/hostname");

    if(!fileh.open(QIODevice::ReadOnly))
    {
        qDebug() << fileh.errorString();
        qDebug() << "ERROR - shutting down - hostname not found or unreadable";
        exit(1);
    }

    QTextStream in(&fileh);
    hostname_ = in.readLine();

    fileh.close();
}

void AppLoop::run()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AppLoop::updateActiveReadings);
    timer->setSingleShot(true);
    timer->singleShot(10, this, &AppLoop::updateActiveReadings);
    timer->setSingleShot(false);
    timer->start(900000);
}

void AppLoop::updateActiveReadings()
{
    QSqlDatabase db = DbConnection::getInstance().db();

    if (db.open())
    {
        QSqlQuery query(db);
        query.exec("SELECT * FROM \"Devices\" WHERE \"Hostname\" = '" + hostname_ + "' AND \"UserId\" = '" + username_ + "'");
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
