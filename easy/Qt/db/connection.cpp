#include "connection.h"
#include "query.h"
#include "model.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QDebug>


Connection::Connection()
{
}

Connection::Connection(const QString &database)
    : _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    _db.setDatabaseName(database);
}

Connection::Connection(const QString &database, const QString &connectionName)
    : _db(QSqlDatabase::addDatabase("QSQLITE", connectionName))
{
    _db.setDatabaseName(database);
}
bool Connection::open()
{
    if( _db.open()) return true;
    qDebug()<<_db.lastError().text();
    return false;
}

bool Connection::close()
{
    if(isOpen()) {
        _db.close();
    }
    return isOpen();
}

bool Connection::isOpen() const
{
    return _db.isOpen();
}

Connection::~Connection()
{
    close();
}

bool Connection::create(const Create &c)
{
    QSqlQuery query = c.query(_db);
    if(!query.exec()) {
        qDebug()<<query.lastError().text();
    }
    return true;
}

int Connection::insert(const Insert &i)
{
    QSqlQuery query = i.query(_db);
    if(!query.exec()) {
        qDebug()<<query.lastError().text();
        return 0;
    }
    return query.lastInsertId().toInt();
}


QList<Model *> Connection::select(const Select &s)
{
    QSqlQuery query = s.query(_db);
    QList<Model *> list;
    if(query.exec()) {
        while(query.next()) {
            Model *model = new Model;
           int length = query.record().count();
            for(int i = 0; i< length; ++i ) {
                QString key = query.record().fieldName(i);
                int index = query.record().indexOf(key);
                model->value(key, query.value(index));
            }
            list.append(model);
        }
    } else {
       qDebug()<< query.lastError().text();
    }

    return list;

}


