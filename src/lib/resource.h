#ifndef RESOURCE_H
#define RESOURCE_H
#include <QtCore>
namespace core {
class Resource
{
public:
    Resource();
    quint64 id() const;
    const QString& tableName() const;

protected:
    void setId(quint64 id);
    void setTableName(const QString& name);

private:
    quint64 mId = -1;
    QString mTableName;

};
}
#endif // RESOURCE_H
