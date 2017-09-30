#include "variantlink.h"
namespace cvar {

VariantLink::VariantLink()
    :Resource()
{

}

VariantLink::VariantLink(const QString &name, const QString &url, const QIcon &icon)
    :Resource(),
    mName(name), mRawUrl(url), mIcon(icon)
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

QString VariantLink::rawUrl() const
{
    return mRawUrl;
}

void VariantLink::setRawUrl(const QString &url)
{
    mRawUrl = url;
}

QIcon VariantLink::icon() const
{
    return mIcon;
}

void VariantLink::setIcon(const QIcon &icon)
{
    mIcon = icon;
}

QUrl VariantLink::toUrl(const Variant &variant) const
{
    QString raw = mRawUrl;
    raw = raw.replace("$CHROM", variant.chromosom());
    raw = raw.replace("$POS", QString::number(variant.position()));
    raw = raw.replace("$REF", variant.ref());
    raw = raw.replace("$ALT", variant.alt());
    return QUrl(raw);
}

bool VariantLink::operator==(const VariantLink &a) const
{
    return a.name() == this->name();
}

}
