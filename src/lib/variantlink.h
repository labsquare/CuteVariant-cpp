#ifndef VARIANTLINK_H
#define VARIANTLINK_H
#include <QtCore>
#include <QtGui>
#include "resource.h"

namespace cvar {
class VariantLink : public Resource
{
public:
    VariantLink();
    VariantLink(const QString& name, const QString& url, const QIcon& icon);

    QString name() const;
    void setName(const QString &name);

    QString url() const;
    void setUrl(const QString &url);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

private:
    QString mName;
    QString mUrl;
    QIcon mIcon;
};
}

#endif // VARIANTLINK_H
