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
    Field();
    Field(const QString& name, const QString& description);

    const QString &name() const;
    const QString &description() const;

private:
    QString mName;
    QString mDescription;
};
}
#endif // FIELD_H
