#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H
#include <QtCore>
#include "project.h"
#include "region.h"
#include "variant.h"
#include "field.h"
#include <QtSql>
class VariantModel : public QAbstractTableModel
{
public:
    enum {
        ChromCol = 0,
        PosCol   = 1,
        RefCol   = 2,
        AltCol   = 3,
        AnnCol   = 4
    };
    VariantModel(Project * prj, QObject * parent = 0x0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setAnnotationColumns(const QStringList& annotationColumns);

    void update();

protected:
    QSqlQuery makeQuery();

private:
    Project * mProject;
    QList<Variation> mVariants;
    QList<Region> mCurrentRegions;
    QStringList mAnnotationColumns;


};

#endif // VARIANTMODEL_H
