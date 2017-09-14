#ifndef RESOURCE_H
#define RESOURCE_H
#include <QtCore>
namespace cvar {
class Resource
{
public:
    Resource();
    quint64 id() const;
    const QString& tableName() const;
    void setId(quint64 id);

    /*!
     * \brief simplified the string to save into sql
     * \param name
     * \return sql valid String
     */
    static QString normalize(const QString& string);

    bool exists() const;


protected:
    void setTableName(const QString& name);

private:
    quint64 mId = -1;
    QString mTableName;

};
}
#endif // RESOURCE_H
