#ifndef FIELDSMODEL_H
#define FIELDSMODEL_H
#include <QAbstractListModel>
#include "field.h"
#include "cutevariant.h"

namespace cvar {
class FieldsModel : public QAbstractListModel
{
public:
    FieldsModel(CuteVariant * prj , QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void load();

private:
    CuteVariant * mProject;
    QList<Field> mDatas;
};

}
#endif // FIELDSMODEL_H
