#ifndef DATAMAPPER_H
#define DATAMAPPER_H
#include <QtCore>
#include <QSqlRecord>
namespace cvar {
template <typename T, typename S>
class DataMapper
{
public:
    DataMapper<T,S> (const QString& name): mTableName(name) {}

    virtual bool insert(const T& record) = 0;
    virtual bool update(const T& record) = 0;
    virtual bool remove(const T& record) = 0;

    virtual T get(int id) const = 0;
    virtual QList<T> list() const = 0;

    virtual void createTable() const = 0;


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

private:
    static S * instance;
    QString mTableName;


};

template <typename T, typename S>
S * DataMapper<T,S>::instance = nullptr;

}
#endif // DATAMAPPER_H
