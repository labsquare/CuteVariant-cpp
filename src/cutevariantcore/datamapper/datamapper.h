#ifndef DATAMAPPER_H
#define DATAMAPPER_H
#include <QtCore>
#include <QtSql>

namespace cvar {
class DataColumn;
class DataColumn {

public:
    DataColumn(const QString& name = QString("default"), QVariant::Type type = QVariant::String, const QString& option = QString())
        :mName(name), mType(type), mOption(option)
    {}

    QString toSql() const {
        return QString("%1 %2 %3").arg(mName, typeName(mType),mOption);
    }

    static QString typeName(QVariant::Type type)
    {
        switch (type)
        {
        case QVariant::Int : return "INTEGER";
        case QVariant::Double : return "REAL";
        case QVariant::Bool : return "INTEGER";
        case QVariant::String : return "TEXT";
        default: return "TEXT";
        }
    }


    QString name() const { return mName ;}

    QVariant::Type type() const {return mType;}

    QString option() const {return mOption;}

private:

    QString mName;
    QVariant::Type mType;
    QString mOption;

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

    virtual T fromSql(const QSqlRecord& record) const  = 0;

    virtual QHash<QString, QVariant> bind(const T& record) const = 0;

    //-----------------------------------------------------------------------------------------------
    virtual bool insert(QList<T>& records) const
    {


        QStringList columns  = columnNames();
        QStringList escape_columns;

        for (const QString& c : columns)
            escape_columns.append(QStringLiteral("`%1`").arg(c));

        QSqlQuery query;
        query.prepare(QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName(),
                                                                     escape_columns.join(","),
                                                                     QString("?").repeated(columns.size()).split("", QString::SkipEmptyParts).join(",")));

        QSqlDatabase::database().transaction();

        for (auto& record : records)
        {
            auto values = bind(record);

            for (int i=0; i< columns.size(); ++i)
                query.bindValue(i, values[columns.at(i)]);

            if (!query.exec())
            {
                qWarning()<<Q_FUNC_INFO<<query.lastQuery();
                qWarning()<<Q_FUNC_INFO<<query.lastError().text();
            }

            record.setId(query.lastInsertId().toInt());
        }

        QSqlDatabase::database().commit();


        return true;
    }

    //-----------------------------------------------------------------------------------------------

    virtual bool update(const T& record) const {

        QStringList columns = columnNames();
        QStringList set;
        auto values = bind(record);

        for (const QString& c : columns)
        {
            if (values.contains(c))
                set.append(QString("`%1`=?").arg(c));

        }

        QSqlQuery query;
        query.prepare(QStringLiteral("UPDATE `%1` SET %2 WHERE rowid = 1").arg(tableName()).arg(set.join(",")));


        for (int i=0; i< columns.size(); ++i)
            query.bindValue(i, values[columns.at(i)]);


        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.executedQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }


        return true;
    }

    //-----------------------------------------------------------------------------------------------
    virtual bool remove(const T& record) const {

        auto b = bind(record);
        if (!b.contains("id")){
            qDebug()<<Q_FUNC_INFO<<"no id avaible for record";
            return false;
        }

        QSqlQuery query(QString("DELETE FROM `%1` WHERE rowid=%2").arg(tableName()).arg(b["id"].toString()));

        if (!query.exec())
        {
            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }

        return true;
    }
    //-----------------------------------------------------------------------------------------------

    virtual bool createTable() const {

        QSqlQuery query;
        query.exec(QStringLiteral("DROP TABLE IF EXISTS %1").arg(tableName()));


        if (!query.exec(QStringLiteral("CREATE TABLE %1 (%2)").arg(tableName()).arg(columnNames().join(","))))
        {
            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
            return false;
        }
        return true;
    }


    //-----------------------------------------------------------------------------------------------

    virtual T get(int id) const {

        QSqlQuery query;

        T record;
        if (query.exec(QString("SELECT rowid, * FROM %1 WHERE rowid = %2").arg(tableName(), id)))
        {
            query.next();
            record = fromSql(query.record());
        }

        return record;
    }

    //-----------------------------------------------------------------------------------------------

    virtual QList<T> list(quint64 limit = 0, quint64 offset = 0) const {

        QList<T> records;
        QSqlQuery query;

        bool success = false;
        if ( !limit  && !offset)
            success = query.exec(QString("SELECT rowid, * FROM %1").arg(tableName()));
        else
            success = query.exec(QString("SELECT rowid, * FROM %1 LIMIT %2 OFFSET %3").arg(tableName()).arg(limit).arg(offset));

        if (success)
        {
            while (query.next())
                records.append(fromSql(query.record()));
        }

        return records;

    }
//-----------------------------------------------------------------------------------------------

protected:

    void addColumn(const QString& name, QVariant::Type type, const QString& option = QString()){

        mColumns[name] = DataColumn{name, type, option};

    }


    QStringList columnNames() const {

        QStringList c ;
        for (const auto& col : mColumns)
            c.append(col.name());

        return c;

    }

    //    // Insert Query
    //    bool sqlInsert(const QHash<QString, QVariant> & data) const {

    //        QStringList keys = data.keys();
    //        QStringList fields;
    //        QStringList fillField;

    //        // add extra quote to fields and values
    //        std::transform(data.keyBegin(), data.keyEnd(), std::back_inserter(fields), [](const auto& i){return "`"+i+"`";});
    //        std::transform(data.keyBegin(), data.keyEnd(), std::back_inserter(fillField), [](const auto& i){return "?";});

    //        QSqlQuery query;

    //        query.prepare(QString("INSERT INTO `%1` (%2) VALUES (%3)")
    //                      .arg(tableName())
    //                      .arg(fields.join(','))
    //                      .arg(fillField.join(',')));


    //        for (int i=0; i<keys.size(); ++i)
    //            query.bindValue(i, data[keys[i]]);

    //        if (!query.exec())
    //        {
    //            qDebug()<<query.executedQuery();
    //            qDebug()<<Q_FUNC_INFO<<query.lastQuery();
    //            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
    //            return false;
    //        }

    //        return true;
    //    }

    //    // Insert Query
    //    bool sqlRemove(int id) const {

    //        QSqlQuery query(QString("DELETE FROM `%1` WHERE id=%2").arg(tableName()).arg(id));

    //        if (!query.exec())
    //        {
    //            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
    //            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
    //            return false;
    //        }

    //        return true;

    //    }

    //    bool sqlUpdate(quint64 id, const QHash<QString, QVariant> & data) const {

    //        QStringList keys = data.keys();

    //        if (keys.contains("id"))
    //            keys.removeAll("id");

    //        QStringList set;

    //        for (const QString& i: keys)
    //            set.append(QString("`%1` = '%2'").arg(i).arg(data[i].toString()));



    //        QSqlQuery query;
    //        if (!query.exec(QString("UPDATE `%1` SET %2 WHERE id=%3")
    //                        .arg(tableName())
    //                        .arg(set.join(","))
    //                        .arg(data["id"].toInt())))



    //        {
    //            qDebug()<<query.lastQuery();
    //            qDebug()<<Q_FUNC_INFO<<query.executedQuery();
    //            qDebug()<<Q_FUNC_INFO<<query.lastError().text();
    //            return false;
    //        }

    //        return true;


    //    }

    //    bool sqlCreateTable(const QHash<QString, QVariant> & data) const {

    //        auto table_data = data;

    //        QStringList field;

    //        if (!table_data.contains("id"))
    //            field.append("id INTEGER PRIMARY KEY AUTOINCREMENT");

    //        auto i = table_data.begin();
    //        while (i != table_data.end())
    //        {
    //            field.append(QString("%1 %2").arg(i.key()).arg(i.value().toString()));
    //            ++i;
    //        }

    //        QSqlQuery query;

    //        query.exec(QStringLiteral("DROP TABLE IF EXISTS %1;").arg(tableName()));
    //        query.exec(QStringLiteral("CREATE TABLE %1 (%2);").arg(tableName()).arg(field.join(",")));
    //        query.exec(QStringLiteral("CREATE INDEX %1_idx ON %1 (id);").arg(tableName()));



    //        return true;


    //    }





private:
    static S * instance;
    QString mTableName;
    QHash<QString, DataColumn> mColumns;



};

template <typename T, typename S>
S * DataMapper<T,S>::instance = nullptr;


}
#endif // DATAMAPPER_H
