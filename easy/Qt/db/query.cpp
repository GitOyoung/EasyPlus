#include "query.h"
#include <QDebug>
Query::Query()
{

}


Connection::Create::Create(const QString &tableName, bool ifNotExists)
    : _tableName(tableName)
    , _ifNotExists(ifNotExists)
{

}

Connection::Create& Connection::Create::colunm(const QString &name, ColunmType type, Features feature)
{
    Colunm col = {name, type, feature};
    _colunms.append(col);
    return *this;
}

QString Connection::Create::featureString(Features feature)
{
    QString string;
    if(feature & PrimaryKey) {
        string.append(" PRIMARY KEY");
    }
    if(feature & Unique) {
        string.append(" UNIQUE");
    }

    if(feature & NotNull) {
        string.append(" NOT NULL");
    }

    //TODO 其他特征

    return string;
}

QString Connection::Create::stringify(const Colunm &colunm)
{
    static const QString typeStringMap[4] = {
       "INTEGER", "REAL", "TEXT", "BLOB"
    };
    QString colString(colunm.name);
    QString typeString = typeStringMap[colunm.type];
    QString feature  = featureString(colunm.feature);

    return colString.append(QString(" %1 %2").arg(typeString).arg(feature));
}

QSqlQuery Connection::Create::query(QSqlDatabase &db) const
{
    QSqlQuery query(db);
    QString prepare = QString("CREATE TABLE %1 %2 (%3)").arg(_ifNotExists? "IF NOT EXISTS" : "").arg(_tableName);
    QString colunms;
    for (const Colunm &col:  _colunms) {
       colunms.append(stringify(col)).append(',');
    }
    colunms = colunms.left(colunms.length() - 1);
    prepare = prepare.arg(colunms);
    qDebug()<<prepare;
    query.prepare(prepare);
    return query;
}


Connection::Insert::Insert(const QString &tableName)
    : _tableName(tableName)
{

}

void Connection::Insert::addColunm(const QString &key, const QVariant &value)
{
    _keys.append(key);
    _values.append(value);
}

QSqlQuery Connection::Insert::query(QSqlDatabase &db) const
{
    QSqlQuery query(db);
    QString prepare = QString("INSERT INTO %1 (%2) VALUES(%3)").arg(_tableName);
    QString colunms;
    QString valuesPlacehoder;
    for(int i = 0, length = _keys.length(); i < length; ++i ) {
        colunms.append(_keys.at(i)).append(',');
        valuesPlacehoder.append("?,");
    }
    colunms = colunms.left(colunms.length() - 1);
    valuesPlacehoder = valuesPlacehoder.left(valuesPlacehoder.length() - 1);
    prepare = prepare.arg(colunms).arg(valuesPlacehoder);
    qDebug()<<prepare;
    query.prepare(prepare);

    for(int i = 0, length = _values.length(); i < length; ++i ) {
        query.bindValue(i, _values.at(i));
    }

    return query;
}

Connection::Select::Select(const QString &tableName)
    : _tableName(tableName)
{

}

void Connection::Select::addField(const QString &field)
{
    _fields.append(field);
}

void Connection::Select::filter(const Where &where)
{
    _where = where;
}

void Connection::Select::clearOrderBy()
{
    _orders.clear();
}

void Connection::Select::orderBy(const QString &name, SortMode by)
{
    OrderBy order = {name, by};
    _orders.append(order);
}

QStringList Connection::Select::fields() const
{
    return _fields;
}

QString Connection::Select::makeOrderByClause() const
{
    if(_orders.isEmpty()) return QString();
    QString clause;
    for(int i = 0, length = _orders.length(); i < length; ++i) {
        const OrderBy &by = _orders.at(i);
        clause.append(QString("%1 %2,").arg(by.name).arg(by.mode == Asc ? "ASC": "DESC"));
    }
    return clause.left(clause.length() - 1);
}

QSqlQuery Connection::Select::query(QSqlDatabase &db) const
{
    QSqlQuery query(db);
    QString prepare = QString("SELECT %1 FROM %2 %3 %4");  //1. 列，2. 表名，3. WHERE子句，4.ORDER BY子句

    //生成列域
    QString colunms;
    for(int i = 0, length = _fields.length(); i < length; ++i) {
        colunms.append(_fields.at(i)).append(',');
    }
    if(_fields.length() > 0) colunms = colunms.left(colunms.length() - 1);

    QString whereClause = _where.clause();
    QString orderByClause = makeOrderByClause();

    QStringList placeHolders = _where.placeHolders();

    prepare = prepare.arg(colunms.isEmpty() ? "*": colunms)
            .arg(_tableName)
            .arg(whereClause.isEmpty()? "": QString("WHERE (%1)").arg(whereClause))
            .arg(orderByClause.isEmpty()? "" : QString("ORDER BY %1").arg(orderByClause));
    qDebug()<<prepare;

    query.prepare(prepare);
    for(int i = 0, length = placeHolders.length(); i < length; ++i) {
        QString placeHolder = placeHolders.at(i);
        query.bindValue(placeHolder, _where.value(placeHolder));
    }
    return query;
}








