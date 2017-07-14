#ifndef RESOURCE_H
#define RESOURCE_H
#include <QtCore>

class Resource
{
public:
    Resource();
    quint64 id() const;

protected:
    void setId(quint64 id);


private:
    quint64 mId = -1;

};

#endif // RESOURCE_H
