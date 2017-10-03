#ifndef REGION_H
#define REGION_H
#include <QtCore>
#include "resource.h"
namespace cvar {
/*!
 * \brief The Region class
 * Contains location as bed format.
 * start = zero based starting position
 * end   = one based ending position
 */
class Region : public Resource
{
public:
    Region();
    Region(const QString& chromosom, quint64 start , quint64 end);

    const QString &chromosom() const;
    void setChromosom(const QString &chromosom);

    quint64 start() const;
    void setStart(const quint64 &start);

    quint64 end() const;
    void setEnd(const quint64 &end);

    quint64 size() const;

private:
    QString mChromosom;
    quint64 mStart;
    quint64 mEnd;


};
}
#endif // REGION_H
