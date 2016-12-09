#ifndef MODEL_H
#define MODEL_H

#include <QSqlDatabase>
#include <QVariant>
#include <QMap>


namespace easy {
namespace db {


class Model
{
public:
    Model();
    Model(const Model& model);

    QVariant value(const QString &key) const;
    Model& value(const QString &key, const QVariant&value);

    QStringList propertyList() const;

    QString toString() const;

private:
    QMap<QString, QVariant> _records;
};

}
}

#endif // MODEL_H
