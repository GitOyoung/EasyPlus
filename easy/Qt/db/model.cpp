#include "model.h"
#include <QString>

Model::Model()
{

}

Model::Model(const Model &model)
    : _records(model._records)
{

}


QVariant Model::value(const QString &key) const
{
    return _records[key];
}

Model& Model::value(const QString &key, const QVariant &value)
{
    _records[key] = value;
    return *this;
}

QStringList Model::propertyList() const
{
    return _records.keys();
}

QString Model::toString() const
{
    QString string;
   QList<QString>keys = _records.keys();
   for(int i = 0, length = keys.length(); i < length; ++i) {
       QString key = keys.at(i);
       string.append(QString("[%1 = %2]").arg(key).arg(_records[key].toString()));
   }
   string.append("\r\n");
   return string;
}




