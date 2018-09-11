#ifndef VIEWDATAMAPPER_H
#define VIEWDATAMAPPER_H
#include "datamapper.h"
#include "view.h"

namespace cvar {

class ViewDataMapper: public DataMapper<View, ViewDataMapper>
{
public:
    ViewDataMapper();

    virtual View fromSql(const QSqlRecord& record) const  override;
    virtual QHash<QString, QVariant> toSql(const View& record) const override;


};


}
#endif // VIEWDATAMAPPER_H
