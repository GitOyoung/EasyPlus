#ifndef WHERE_H
#define WHERE_H

#include <QVariant>

class Where
{
public:
    enum Logic {
        Logic_Or,
        Logic_And
    };

    enum Relation {
        Relation_Equal,
        Relation_NoEqual,
        Relation_Less,
        Relation_LessOrEqual,
        Relation_Greater,
        Relation_GreaterOrEqual,
        Relation_Between,
        Relation_In,
        Relation_NotIn,
    };
    Where();
    Where(const Where& other);
    Where(const QString& name, Relation rel, const QVariant& value);
    Where(const Where& one, Logic logic, const Where& other);

    Where& logicAnd(const Where&other);
    Where& logicOr(const Where& other);

    Where& addWhere(Logic, const Where& other);

    bool isValid() const;

    QString clause() const;
    QStringList keys() const;
    QVariant value(const QString& key) const;



    static const QString relationMap[9];
public:
    static QString placeholder(const QString &old);
private:
    bool _groupMode;
    bool _valid;

    struct {
        QString name;
        Relation relation;
        QVariant value;
    } v0;

    struct {
        QList<Where> where;
        QList<Logic> logics;
    }v1;


};
#endif // WHERE_H
