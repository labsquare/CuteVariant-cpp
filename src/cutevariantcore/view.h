#ifndef VARIANTTABLE_H
#define VARIANTTABLE_H
#include <QtCore>

namespace cvar{

class View
{
public:
    View(const QString& name = QString(), const QString& description = QString(), int count = 0, const QString& sql = QString());


    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int count() const;
    void setCount(int count);

    QString sql() const;
    void setSql(const QString &sql);

    quint64 id() const;
    void setId(const quint64 &id);

    View unionWith(const View& other) const;
    View intersectWith(const View& other) const;
    View exceptWith(const View& other) const;

    View operator+(const View& other) const;
    View operator-(const View& other) const;
    View operator&(const View& other) const;


private:
    QString mName;
    QString mDescription;
    int mCount = 0;
    QString mSql;
    quint64 mId = 0; // mandatory for template
};

}

#endif // SELECTION_H
