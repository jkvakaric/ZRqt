#include "reading.h"
#include <QDateTime>
#include <QUuid>

Reading::Reading(QString activeReadingId, QString deviceId, QString name, QString ownerUserId, QString readValue, QString readingTypeId, QObject *parent) : QObject(parent)
{
    id_ = QUuid::createUuid().toString();
    activeReadingId_ = activeReadingId;
    deviceId_ = deviceId;
    name_ = name;
    ownerUserId_ = ownerUserId;
    readValue_ = readValue;
    readingTypeId_ = readingTypeId;
    timestamp_ = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
}

QString Reading::id() const
{
    return id_;
}

QString Reading::activeReadingId() const
{
    return activeReadingId_;
}

QString Reading::deviceId() const
{
    return deviceId_;
}

QString Reading::name() const
{
    return name_;
}

QString Reading::ownerUserId() const
{
    return ownerUserId_;
}

QString Reading::readValue() const
{
    return readValue_;
}

QString Reading::readingTypeId() const
{
    return readingTypeId_;
}

QString Reading::timestamp() const
{
    return timestamp_;
}
