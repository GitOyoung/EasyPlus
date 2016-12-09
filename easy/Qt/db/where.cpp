#include "where.h"
#include <QDebug>

namespace easy {
namespace db {


Where::Where()
    : _groupMode(false)
    , _valid(false)
{

}

const QString Where::relationMap[9] = {
   "=", "<>", "<", "<=", ">", ">=", " BETWEEN ", " IN ", " NOT IN "
};

Where::Where(const QString &name, Relation rel, const QVariant &value)
    : _groupMode(false)
    , _valid(true)
    , v0({name, rel, value})
{

}


Where::Where(const Where &one, Logic logic, const Where &other)
    : _groupMode(true)
    , _valid(true)
{
    v1.where.append(one);
    v1.where.append(other);
    v1.logics.append(logic);
}

Where::Where(const Where &other)
    : _groupMode(other._groupMode)
    , _valid(other._valid)
{
    if(_groupMode) {
        v1 = other.v1;
    } else {
        v0 = other.v0;
    }
}

Where& Where::addWhere(Logic logic, const Where &other)
{
    if(_valid) {
        if( !_groupMode) {
            v1.where.clear();
            v1.logics.clear();
            v1.where.append(Where(*this));
            _groupMode = true;
        }
        v1.logics.append(logic);
    }
    v1.where.append(other);
    _valid = true;
    return *this;
}

Where& Where::logicAnd(const Where &other)
{
    Where me(*this);
    v1.where.clear();
    v1.logics.clear();
    v1.where.append(me);
    v1.logics.append(Logic_And);
    v1.where.append(other);
    _groupMode = true;
    _valid = true;
    return *this;
}

Where& Where::logicOr(const Where &other)
{
    Where me(*this);
    v1.where.clear();
    v1.logics.clear();
    v1.where.append(me);
    v1.logics.append(Logic_Or);
    v1.where.append(other);
    _groupMode = true;
    _valid = true;
    return *this;
}

bool Where::isValid() const
{
    return _valid;
}

QString Where::placeholder(const QString &old)
{
    return QString(":%1").arg(old);
}

QStringList Where::keys() const
{
    QStringList list;
    if(_groupMode) {
        for(int i = 0, length = v1.where.length(); i < length; ++i) {
            list.append(v1.where.at(i).keys());
        }
    } else {
        list.append(v0.name);
    }
    return list;
}

QVariant Where::value(const QString &key) const
{
    if(!_groupMode) return key == v0.name ? v0.value : QVariant();
    for(int i = 0, length = v1.where.length(); i < length; ++i) {
        QVariant value = v1.where.at(i).value(key);
        if(!value.isNull())  return value;
    }
    return QVariant();
}


QString Where::clause() const
{
    if(!isValid()) return QString();
    if(_groupMode) {
        QString str = QString("(%1)").arg(v1.where.at(0).clause());
        int length = v1.logics.length();
        for(int i = 0; i < length; ++i) {
            str.append(v1.logics.at(i) == Logic_And ? " AND ": " OR ");
            str.append(QString("(%1)").arg(v1.where.at(i + 1).clause()));
        }
        return str;
    } else {

        return QString("%1%2%3").arg(v0.name).arg(relationMap[v0.relation]).arg(QString(":%1").arg(v0.name));
    }
}



}
}
