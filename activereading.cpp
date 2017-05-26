#include "activereading.h"
#include "dbconnection.h"
#include "reading.h"
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

ActiveReading::ActiveReading(QObject *parent) : QObject(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ActiveReading::update);
    timer->setSingleShot(true);
    timer->singleShot(10, this, &ActiveReading::update);
    timer->setSingleShot(false);
    timer->start(305000);
}

ActiveReading::ActiveReading(QString id, QString dataFilepath, QString deviceId, QString name, QString ownerUserId, QString readingTypeId, QObject *parent) : ActiveReading(parent)
{
    id_ = id;
    dataFilepath_ = dataFilepath;
    deviceId_ = deviceId;
    name_ = name;
    ownerUserId_ = ownerUserId;
    readingTypeId_ = readingTypeId;
}

void ActiveReading::update()
{
    QFile file(this->dataFilepath_);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        qDebug() << "WARNING - sensor reading source file (" + dataFilepath_ + ") not found or unreadable";
        return;
    }

    QTextStream in(&file);
    QString read = in.readAll();
    QString readValue = read.section("t=", 1, 1, QString::SectionSkipEmpty).trimmed();
    readValue.insert(readValue.size() - 3, '.');

    file.close();

    QSqlDatabase db = DbConnection::getInstance().db();

    if (db.open())
    {
        Reading *reading = new Reading(
                    this->id_,
                    this->deviceId_,
                    this->name_,
                    this->ownerUserId_,
                    readValue,
                    this->readingTypeId_);

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

QString ActiveReading::id() const
{
    return id_;
}

QString ActiveReading::dataFilepath() const
{
    return dataFilepath_;
}

QString ActiveReading::deviceId() const
{
    return deviceId_;
}

QString ActiveReading::name() const
{
    return name_;
}

QString ActiveReading::ownerUserId() const
{
    return ownerUserId_;
}

QString ActiveReading::readingTypeId() const
{
    return readingTypeId_;
}
