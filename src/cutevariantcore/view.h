#ifndef VARIANTTABLE_H
#define VARIANTTABLE_H
#include <QtCore>
#include "abstractrecord.h"

namespace cvar{

class View : public AbstractRecord
{
public:
    View(const QString& name, const QString& description, int count);


    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int count() const;
    void setCount(int count);

    QString sql() const;
    void setSql(const QString &sql);


    // virtual methods
    virtual bool update() override;
    virtual bool insert() override;
    virtual bool remove() override;

    virtual void fromSql(const QSqlRecord& record) override;

    // static methods
    static void createTable();



private:
    QString mName;
    QString mDescription;
    int mCount = 0;
    QString mSql;
};

}

#endif // SELECTION_H
