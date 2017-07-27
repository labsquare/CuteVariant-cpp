#ifndef RESULTTREEMODEL_H
#define RESULTTREEMODEL_H
#include <QAbstractItemModel>
#include <QtSql>
#include <QSqlRecord>
#include "project.h"
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
    bool hasChildren(const QModelIndex &parent) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex& parent) override;

    int totalVariantCount() const;


    void load();

private:
    core::Project * mProject;
    QList<QSqlRecord> mRecords;
    QHash<int, QList<QSqlRecord>> mChilds;

};

#endif // RESULTTREEMODEL_H
