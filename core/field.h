#ifndef FIELD_H
#define FIELD_H
#include <QtCore>

class Field
{
public:
    Field();
    Field(const QString& name, const QString& description);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int id() const;
    void setId(int id);

private:
    int mId = -1;
    QString mName;
    QString mDescription;
    QVariant::Type mType = QVariant::Invalid;
};

#endif // FIELD_H
