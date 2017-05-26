#ifndef READING_H
#define READING_H

#include <QObject>

class Reading : public QObject
{
    Q_OBJECT

private:
    QString id_;
    QString activeReadingId_;
    QString deviceId_;
    QString name_;
    QString ownerUserId_;
    QString readValue_;
    QString readingTypeId_;
    QString timestamp_;

public:
    explicit Reading(QString activeReadingId, QString deviceId, QString name, QString ownerUserId, QString readValue, QString readingTypeId, QObject *parent = 0);
    QString id() const;
    QString activeReadingId() const;
    QString deviceId() const;
    QString name() const;
    QString ownerUserId() const;
    QString readValue() const;
    QString readingTypeId() const;
    QString timestamp() const;

};

#endif // READING_H
