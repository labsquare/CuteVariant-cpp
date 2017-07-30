#ifndef RESULTTREEMODEL_H
#define RESULTTREEMODEL_H
#include <QAbstractItemModel>
#include <QtSql>
#include <QSqlRecord>
#include "project.h"
#include "variantquery.h"

class ResultTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ResultTreeModel(core::Project * prj, QObject * parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool hasChildren(const QModelIndex &parent) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex& parent) override;


    int totalRowCount() const;
    void setQuery(const core::VariantQuery& q);

    QSqlRecord record(const QModelIndex& index);


public Q_SLOTS:
    void load(int offset = 0, int limit = 100);

private:
    core::Project * mProject;
    core::VariantQuery mCurrentQuery;
    QList<QSqlRecord> mRecords;
    QHash<int, QList<QSqlRecord>> mChilds;
    int mTotalRowCount = 0;


};

#endif // RESULTTREEMODEL_H
