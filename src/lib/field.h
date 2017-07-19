#ifndef FIELD_H
#define FIELD_H
#include <QtCore>
#include "resource.h"

namespace core {

/*!
 * \brief The Field class contains Annotation description
 * @see sql field table
 */
class Field : public Resource
{
public:
    enum Type
    {
        INTEGER,
        REAL,
        TEXT,
        BOOL
    };

    Field();
    Field(const QString& colname, const QString& name, const QString& description = QString(), const Type& type = Field::TEXT);

     const QString& colname() const;
     const QString &name() const;
     const QString &description() const;
     Type type() const;

     QString typeName() const;
     QString sqliteType() const;

private:
    QString mColname;
    QString mName;
    QString mDescription;
    Type mType = Field::TEXT;
};
}
#endif // FIELD_H
