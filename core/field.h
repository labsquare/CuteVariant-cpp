#ifndef FIELD_H
#define FIELD_H
#include <QtCore>

class Field
{
public:
    Field();
    Field(int sqlId, const QString& name, const QString& description);

    const QString &name() const;
    const QString &description() const;
    int sqlId() const;

private:
    QString mName;
    QString mDescription;
    int msqlId = -1;

};

#endif // FIELD_H
