#ifndef VARIANTLINK_H
#define VARIANTLINK_H
#include <QtCore>
#include <QtGui>
#include "resource.h"
#include "variant.h"

namespace cvar {
class VariantLink : public Resource
{
public:
    VariantLink();
    VariantLink(const QString& name, const QString& rawUrl, const QIcon& icon);

    QString name() const;
    void setName(const QString &name);

    QString rawUrl() const;
    void setRawUrl(const QString &rawUrl);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QUrl toUrl(const Variant& variant) const;

private:
    QString mName;
    QString mRawUrl;
    QIcon mIcon;
};
}

#endif // VARIANTLINK_H
