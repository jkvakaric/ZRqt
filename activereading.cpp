#include "activereading.h"
#include "dbconnection.h"
#include "reading.h"
#include "rtid.h"
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QUuid>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

ActiveReading::ActiveReading(QString id, QString dataFilepath, QString deviceId, QString name, QString ownerUserId, QString readingTypeId, QObject *parent) : QObject(parent),
    id_(id),
    dataFilepath_(dataFilepath),
    deviceId_(deviceId),
    name_(name),
    ownerUserId_(ownerUserId),
    readingTypeId_(readingTypeId)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ActiveReading::update);
    timer->setSingleShot(true);
    timer->singleShot(10, this, &ActiveReading::update);
    timer->setSingleShot(false);
    timer->start(305000);
}

void ActiveReading::update()
{
    Reading *reading = Reading::make_reading(RTIDMap::map.value(readingTypeId_));

    if(reading != nullptr)
    {
        reading->measure(dataFilepath_);

        QSqlDatabase db = DbConnection::getInstance().db();

        if (db.open())
        {
            reading->setId(QUuid::createUuid().toString());
            reading->setActiveReadingId(id_);
            reading->setDeviceId(deviceId_);
            reading->setName(name_);
            reading->setOwnerUserId(ownerUserId_);
            reading->setReadingTypeId(readingTypeId_);
            reading->setTimestamp(QDateTime::currentDateTime().toString(Qt::ISODate));

            QSqlQuery query(db);
            QString queryString = "INSERT INTO \"Readings\" ( \"Id\", \"ActiveReadingId\", \"DeviceId\", "
                          "\"Name\", \"OwnerUserId\", \"ReadValue\", \"ReadingTypeId\", \"Timestamp\" ) "
                          "VALUES ( '" + reading->id() + "', '" + reading->activeReadingId() + "', '" + reading->deviceId() + "', "
                          "'" + reading->name() + "', '" + reading->ownerUserId() + "', '" + reading->readValue() + "', "
                          "'" + reading->readingTypeId() + "', '" + reading->timestamp() + "' )";

            if (query.exec(queryString))
                qDebug() << "SUCCESS - " + queryString;

            delete reading;
        }
        else qDebug() << db.lastError();
    }
    else qDebug() << "WARNING - ReadingType specified does not exist";
}
