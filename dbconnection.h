#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql/QSqlDatabase>

class DbConnection
{

private:
    DbConnection();
    QSqlDatabase db_;

public:
    static DbConnection& getInstance();
    DbConnection(DbConnection const&) = delete;
    void operator = (DbConnection const&) = delete;
    QSqlDatabase db() const;

};

#endif // DBCONNECTION_H
