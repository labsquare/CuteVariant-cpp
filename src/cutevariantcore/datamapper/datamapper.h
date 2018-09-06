#ifndef DATAMAPPER_H
#define DATAMAPPER_H
#include <QtCore>
#include <QtSql>

namespace cvar {



class User;

class AbstractField{};

template <typename T>
class Field : public AbstractField {
public:

    using Fct = T (User::*)();

    Field(Fct a)
        :mA(a){}

    Fct mA;


};



template <typename T, typename S>
class DataMapper
{
public:
    DataMapper<T,S> (const QString& name): mTableName(name) {}


    static S * i()
    {
        if (instance == nullptr)
            instance = new S();
        return instance;

    };


    inline void setTableName(const QString& name){
        mTableName = name;
    }

    inline const QString& tableName() const {
        return mTableName;
    }


    virtual bool insert(const T& record) const = 0;
    virtual bool update(const T& record) const = 0;
    virtual bool remove(const T& record) const = 0;
    virtual bool createTable() const = 0;
    virtual T fromSql(const QSqlRecord& record) const  = 0;

    virtual T get(int id) const {

        QSqlQuery query(QString("SELECT * FROM %1 WHERE id = %2").arg(tableName()).arg(id));
        if (query.next())
            return fromSql(query.record());

        return T();
    }

    virtual QList<T> list(quint64 limit = 0, quint64 offset = 0) const {

        QList<T> list;
        QSqlQuery query;
        if (!limit)
            query.prepare(QString("SELECT * FROM %1").arg(tableName()));

        else
            query.prepare(QString("SELECT * FROM %1 LIMIT %2 OFFSET %3").arg(tableName()).arg(limit).arg(offset));

        if (!query.exec())
        {
            qDebug()<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return list;
        }


        while (query.next())
            list.append(fromSql(query.record()));


        return list;
    }


protected:

    // Insert Query
    bool sqlInsert(const QHash<QString, QVariant> & data) const {

        QStringList keys = data.keys();
        QStringList fields;
        QStringList fillField;

        // add extra quote to fields and values
        std::transform(data.keyBegin(), data.keyEnd(), std::back_inserter(fields), [](const auto& i){return "`"+i+"`";});
        std::transform(data.keyBegin(), data.keyEnd(), std::back_inserter(fillField), [](const auto& i){return "?";});

        QSqlQuery query;

        query.prepare(QString("INSERT INTO `%1` (%2) VALUES (%3)")
                      .arg(tableName())
                      .arg(fields.join(','))
                      .arg(fillField.join(',')));


        for (int i=0; i<keys.size(); ++i)
            query.bindValue(i, data[keys[i]]);

        if (!query.exec())
        {
            qDebug()<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }

        return true;
    }

    // Insert Query
    bool sqlRemove(int id) const {

        QSqlQuery query(QString("DELETE FROM `%1` WHERE id=%2").arg(tableName()).arg(id));

        if (!query.exec())
        {
            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }

        return true;

    }

    bool sqlUpdate(const QHash<QString, QVariant> & data) const {

        QStringList keys = data.keys();

        if (!keys.contains("id"))
        {
            qDebug()<<Q_FUNC_INFO<<"record has no id";
            return false;
        }

        quint64 id = data["id"].toInt();
        keys.removeAll("id");

        QStringList set;

        for (const QString& i: keys)
            set.append(QString("`%1` = '%2'").arg(i).arg(data[i].toString()));



        QSqlQuery query;
        if (!query.exec(QString("UPDATE `%1` SET %2 WHERE id=%3")
                      .arg(tableName())
                      .arg(set.join(","))
                      .arg(data["id"].toInt())))



        {
            qDebug()<<query.lastQuery();
            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }

        return true;


    }

    bool sqlCreateTable(const QHash<QString, QVariant> & data) const {

        auto table_data = data;

        QStringList field;

        if (!table_data.contains("id"))
            field.append("id INTEGER PRIMARY KEY AUTOINCREMENT");

        auto i = table_data.begin();
        while (i != table_data.end())
        {
            field.append(QString("%1 %2").arg(i.key()).arg(i.value().toString()));
            ++i;
        }

        QSqlQuery query;

        query.exec(QStringLiteral("DROP TABLE IF EXISTS %1;").arg(tableName()));
        query.exec(QStringLiteral("CREATE TABLE %1 (%2);").arg(tableName()).arg(field.join(",")));
        query.exec(QStringLiteral("CREATE INDEX %1_idx ON %1 (id);").arg(tableName()));


        if (!query.exec())
        {
            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }

        return true;


    }





private:
    static S * instance;
    QString mTableName;



};

template <typename T, typename S>
S * DataMapper<T,S>::instance = nullptr;

}
#endif // DATAMAPPER_H
