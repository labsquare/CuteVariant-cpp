#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H
#include <QAbstractListModel>
#include "field.h"
#include "project.h"

namespace cvar {
class FieldsModel : public QAbstractListModel
{
public:
    FieldsModel(Project * prj , QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void load();

private:
    Project * mProject;
    QList<Field> mDatas;
};

}
#endif // FIELDSMODEL_H
