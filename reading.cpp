#include "readingtemperatureonewire.h"
#include "reading.h"
#include "rtid.h"
#include <QDateTime>
#include <QUuid>

Reading::Reading(QObject *parent) : QObject(parent) { }

Reading* Reading::make_reading(int readingTypeId)
{
    if(readingTypeId == RTID::TemperatureOneWire)
        return new ReadingTemperatureOneWire;
    else return nullptr;
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

void Reading::setId(const QString &id)
{
    id_ = id;
}

void Reading::setActiveReadingId(const QString &activeReadingId)
{
    activeReadingId_ = activeReadingId;
}

void Reading::setDeviceId(const QString &deviceId)
{
    deviceId_ = deviceId;
}

void Reading::setName(const QString &name)
{
    name_ = name;
}

void Reading::setOwnerUserId(const QString &ownerUserId)
{
    ownerUserId_ = ownerUserId;
}

void Reading::setReadingTypeId(const QString &readingTypeId)
{
    readingTypeId_ = readingTypeId;
}

void Reading::setTimestamp(const QString &timestamp)
{
    timestamp_ = timestamp;
}
