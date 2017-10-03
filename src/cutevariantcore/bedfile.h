#ifndef BEDFILE_H
#define BEDFILE_H
#include "resource.h"

namespace cvar {

class BedFile : public Resource
{
public:
    BedFile();
    BedFile(const QString& filename, int count);


    const QString& filename() const;
    void setFilename(const QString &filename);

    quint64 count() const;
    void setCount(const quint64 &count);

private:
    QString mFilename;
    quint64 mCount;
};

}
#endif // BEDFILE_H
