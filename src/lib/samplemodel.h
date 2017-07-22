#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H
#include <QAbstractListModel>
#include "sample.h"
#include "project.h"
namespace core{
class SampleModel : public QAbstractListModel
{
public:
    SampleModel(Project * prj, QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void load();

private:
    QList<Sample> mDatas;
    Project * mProject;
};
}

#endif // SAMPLEMODEL_H
