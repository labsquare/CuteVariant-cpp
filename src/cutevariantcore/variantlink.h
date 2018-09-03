#ifndef VARIANTLINK_H
#define VARIANTLINK_H
#include <QtCore>
#include <QtGui>
#include "abstractrecord.h"
#include "variant.h"

namespace cvar {
class VariantLink : public AbstractRecord
{
public:
    VariantLink(const QString& name = QString(), const QString& rawUrl = QString(), const QIcon& icon = QIcon());

//    QString name() const;
//    void setName(const QString &name);

//    QString rawUrl() const;
//    void setRawUrl(const QString &rawUrl);

//    QIcon icon() const;
//    void setIcon(const QIcon &icon);

//    QUrl toUrl(const Variant& variant) const;

//    bool operator==(const VariantLink &a) const;

private:

};
}

#endif // VARIANTLINK_H
