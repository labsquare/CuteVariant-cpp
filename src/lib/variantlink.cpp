#include "variantlink.h"
namespace cvar {

VariantLink::VariantLink()
    :Resource()
{

}

VariantLink::VariantLink(const QString &name, const QString &url, const QIcon &icon)
    :Resource(),
    mName(name), mUrl(url), mIcon(icon)
{

}

QString VariantLink::name() const
{
    return mName;
}

void VariantLink::setName(const QString &name)
{
    mName = name;
}

QString VariantLink::url() const
{
    return mUrl;
}

void VariantLink::setUrl(const QString &url)
{
    mUrl = url;
}

QIcon VariantLink::icon() const
{
    return mIcon;
}

void VariantLink::setIcon(const QIcon &icon)
{
    mIcon = icon;
}

}
