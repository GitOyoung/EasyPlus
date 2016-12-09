#ifndef QUERY_H
#define QUERY_H
#include "connection.h"
#include "where.h"
#include <QSqlQuery>
#include <QVariant>

class Query
{
public:
    enum ColunmType {
        Integer,        Real,        Text,        Blob
    };

    enum Feature {
        None = 0, PrimaryKey = 0x00000001, NotNull = 0x00000002,    Unique = 0x00000004,
        Autocreament = 0x00000008,
    };
    typedef int  Features;

    struct Colunm {
        QString name;
        ColunmType type;
        Features feature;
        QVariant defaultValue;
    };

    enum SortMode {
        Asc,
        Desc
    };

    struct OrderBy {
        QString name;
        SortMode mode;
    };

    Query();
    virtual QSqlQuery query(QSqlDatabase& db) const { return QSqlQuery(db);}
    virtual ~Query(){}
};

class Connection::Create: public Query
{
public:

    Create(const QString & tableName, bool ifNotExists = false);
    Create& colunm(const QString& name, ColunmType type, Features feature,const QVariant& defaultValue = QVariant());

    QSqlQuery query(QSqlDatabase &db) const;
protected:
    static QString featureString(Features feature);
    static QString stringify(const Colunm& colunm);
    static QString defaultValueString(const QVariant& def);
private:
    QString _tableName;
    bool _ifNotExists;

    QList<Colunm> _colunms;
};

class Connection::Insert: public Query
{
public:
    Insert(const QString& tableName);
    Insert(const Model& model);
    void setTableName(const QString &tableName);
    void addColunm(const QString&key, const QVariant& value);
    virtual QSqlQuery query(QSqlDatabase &db) const;
private:
    QString _tableName;
    QStringList _keys;
    QList<QVariant> _values;
};


class Connection::Select: public Query
{
public:
    Select(const QString &tableName);
    void addField(const QString& field);
    void filter(const Where& where);
    void orderBy(const QString &name, SortMode by);
    void clearOrderBy();

    QStringList fields() const;

    QSqlQuery query(QSqlDatabase &db) const;
protected:
    QString makeOrderByClause() const;
private:
    Where _where;
    QStringList _fields;
    QString _tableName;
    QList<OrderBy> _orders;
};

class Connection::Update: public Query
{
public:
    Update(const Update& other);
    Update(const QString& tableName, const QString &key, const QVariant& value);

    void add(const QString &key, const QVariant& value);
    void filter(const Where&where);

    QSqlQuery query(QSqlDatabase &db) const;
protected:
    QString makeSetClause() const;
    QStringList placeholders() const;
    static QString placeholder(const QString &old);
private:
    QString _tableName;
    Where _where;
    QMap<QString, QVariant> _content;
};

#endif // QUERY_H
