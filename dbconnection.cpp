#include "dbconnection.h"
#include <QFile>
#include <QDebug>

DbConnection::DbConnection()
{
    QFile file("dbconfig");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        qDebug() << "ERROR - shutting down - database config not found or unreadable";
        exit(1);
    }

    QTextStream in(&file);

    QString hostname = in.readLine();
    QString dbname = in.readLine();
    QString username = in.readLine();
    QString password = in.readLine();

    file.close();

    db_ = QSqlDatabase::addDatabase("QPSQL", dbname);

    db_.setHostName(hostname);
    db_.setDatabaseName(dbname);
    db_.setUserName(username);
    db_.setPassword(password);
}

DbConnection& DbConnection::getInstance()
{
    static DbConnection instance;
    return instance;
}

QSqlDatabase DbConnection::db() const
{
    return db_;
}
