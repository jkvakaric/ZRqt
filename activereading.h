#ifndef ACTIVEREADING_H
#define ACTIVEREADING_H

#include <QString>
#include <QObject>

class ActiveReading : public QObject
{
    Q_OBJECT

private:
    explicit ActiveReading(QObject *parent = 0);
    QString id_;
    QString dataFilepath_;
    QString deviceId_;
    QString name_;
    QString ownerUserId_;
    QString readingTypeId_;

public:
    explicit ActiveReading(QString id, QString dataFilepath, QString deviceId, QString name, QString ownerUserId, QString readingTypeId, QObject *parent = 0);
    QString id() const;
    QString dataFilepath() const;
    QString deviceId() const;
    QString name() const;
    QString ownerUserId() const;
    QString readingTypeId() const;

public slots:
    void update();

};

#endif // ACTIVEREADING_H
