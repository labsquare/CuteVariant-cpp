#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H
#include <QAbstractListModel>
#include "project.h"

namespace core {

class VariantModel : public QAbstractListModel
{
    Q_OBJECT
public:
    VariantModel(QObject * parent = nullptr);
    void setProjet(Project * prj);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public Q_SLOTS:
    void setQuery(const QString& raw);

private:
    Project * mPrj = nullptr;

    QList<Variant> mVariants;



};
}
#endif // VARIANTMODEL_H
