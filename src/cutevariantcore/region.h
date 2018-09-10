#ifndef REGION_H
#define REGION_H
#include <QtCore>
namespace cvar {
/*!
 * \brief The Region class
 * Contains location as bed format.
 * start = zero based starting position
 * end   = one based ending position
 */
class Region
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


    quint64 id() const;
    void setId(const quint64 &id);

private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;
    quint64 mId = 0;


};
}
#endif // REGION_H
