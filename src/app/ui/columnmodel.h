#ifndef COLUMNMODEL_H
#define COLUMNMODEL_H
#include <QStandardItemModel>
#include "project.h"
#include "field.h"
#include "sample.h"

class ColumnModel : public QStandardItemModel
{
public:
    ColumnModel(core::Project * prj, QObject * parent = nullptr);

    void load();


private:

core::Project * mProject;


};

#endif // COLUMNMODEL_H
