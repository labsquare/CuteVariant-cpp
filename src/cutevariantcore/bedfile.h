#ifndef BEDFILE_H
#define BEDFILE_H
#include "abstractrecord.h"

namespace cvar {

class BedFile : public AbstractRecord
{
public:
    BedFile(const QString& filename = QString(), int count = 0);


    const QString& filename() const;
    void setFilename(const QString &filename);

    quint64 count() const;
    void setCount(const quint64 &count);


    // virtual methods
    virtual bool update() override;
    virtual bool insert() override;
    virtual bool remove() override;

    virtual void fromSql(const QSqlRecord& record) override;

    // static methods
    static void createTable();



private:
    QString mFilename;
    quint64 mCount;
};

}
#endif // BEDFILE_H
