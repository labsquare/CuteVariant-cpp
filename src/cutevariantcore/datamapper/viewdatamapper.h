#ifndef VIEWDATAMAPPER_H
#define VIEWDATAMAPPER_H
#include "datamapper.h"
#include "view.h"

namespace cvar {

class ViewDataMapper: public DataMapper<View, ViewDataMapper>
{
public:
    ViewDataMapper();
};


}
#endif // VIEWDATAMAPPER_H
