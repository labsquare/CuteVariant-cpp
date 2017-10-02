#ifndef VARIANTTABLE_H
#define VARIANTTABLE_H
#include <QtCore>
namespace cvar{

class VariantSet
{
public:
    VariantSet();
    VariantSet(const QString& name, const QString& description, int count);


    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int count() const;
    void setCount(int count);

    QString sql() const;
    void setSql(const QString &sql);

private:
    QString mName;
    QString mDescription;
    int mCount = 0;
    QString mSql;
};

}

#endif // SELECTION_H
