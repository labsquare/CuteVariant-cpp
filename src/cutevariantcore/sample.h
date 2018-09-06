#ifndef SAMPLE_H
#define SAMPLE_H
#include <QtCore>

namespace cvar {
class Sample;
class Sample
{
public:
    Sample(const QString& name = QString());

    const QString& name() const;
    void setName(const QString& name);


    quint64 id() const;
    void setId(const quint64 &id);

private:
    QString mName;
    quint64 mId;
};
}
#endif // SAMPLE_H
