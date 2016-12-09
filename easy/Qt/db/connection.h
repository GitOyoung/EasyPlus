#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QList>

namespace easy {
namespace db {


class Model;

class Connection
{
public:
    class Create;
    class Insert;
    class Update;
    class Select;
    class Delete;
public:
    Connection();
    Connection(const QString& database);
    Connection(const QString& database, const QString& connectionName);

    /**
     * @brief open 打开连接
     * @return 是否操作成功
     */
    bool open();

    /**
     * @brief close 关闭连接
     * @return
     */
    bool close();
    bool isOpen() const; //是否打开

    /**
     * @brief create 新建表
     * @param c
     * @return
     */
    bool create(const Create& c);
    /**
     * @brief insert
     * @param i
     * @return  返回新插入的id
     */
    int insert(const Insert& i);
    /**
     * @brief update
     * @param u
     * @return 成功则返回受影响的行数，否则返回-1
     */
    int update(const Update& u);
    QList<Model> select(const Select & s);
    int del(const Delete& d);

    ~Connection();
private:
    QSqlDatabase _db;
};

}
}

#endif // CONNECTION_H
