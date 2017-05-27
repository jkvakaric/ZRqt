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
    QString readingTypeId_;
    QString timestamp_;

protected:
    QString readValue_;

public:
    explicit Reading(QObject *parent = 0);
    QString id() const;
    QString activeReadingId() const;
    QString deviceId() const;
    QString name() const;
    QString ownerUserId() const;
    QString readValue() const;
    QString readingTypeId() const;
    QString timestamp() const;
    void setId(const QString &id);
    void setActiveReadingId(const QString &activeReadingId);
    void setDeviceId(const QString &deviceId);
    void setName(const QString &name);
    void setOwnerUserId(const QString &ownerUserId);
    void setReadingTypeId(const QString &readingTypeId);
    void setTimestamp(const QString &timestamp);
    static Reading* make_reading(int readingTypeId);
    virtual void measure(QString dataFilepath) = 0;

};

#endif // READING_H
