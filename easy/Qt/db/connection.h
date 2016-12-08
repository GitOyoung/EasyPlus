#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QList>

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
    int insert(const Insert& i);
    bool update(const Update& u);
    QList<Model*> select(const Select & s);
    int del(const Delete& d);

    ~Connection();
private:
    QSqlDatabase _db;
};

#endif // CONNECTION_H
