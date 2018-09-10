#ifndef DATARECORD_H
#define DATARECORD_H
#include <QtCore>

namespace cvar {
class DataRecord
{
public:
    DataRecord();


    int id() const;
    void setId( int id);

private:
    int mId = 0;
};

}

#endif // DATARECORD_H
