#ifndef REGION_H
#define REGION_H
#include <QtCore>
#include "abstractrecord.h"
namespace cvar {
/*!
 * \brief The Region class
 * Contains location as bed format.
 * start = zero based starting position
 * end   = one based ending position
 */
class Region : public AbstractRecord
{
public:
    Region(const QString& chromosom = QString(), quint64 start=0 , quint64 end=0);

    const QString &chromosom() const;
    void setChromosom(const QString &chromosom);

    quint64 start() const;
    void setStart(const quint64 &start);

    quint64 end() const;
    void setEnd(const quint64 &end);

    quint64 size() const;


    // virtual methods
    virtual bool update() override;
    virtual bool insert() override;
    virtual bool remove() override;

    virtual void fromSql(const QSqlRecord& record) override;

    // static methods
    static void createTable();



private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;


};
}
#endif // REGION_H
