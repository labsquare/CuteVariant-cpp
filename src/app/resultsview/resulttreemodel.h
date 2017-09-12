#ifndef RESULTTREEMODEL_H
#define RESULTTREEMODEL_H
#include <QAbstractItemModel>
#include <QtSql>
#include <QSqlRecord>
#include <QTextStream>
#include "project.h"
#include "variantquery.h"

class ResultTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ResultTreeModel(QObject * parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool hasChildren(const QModelIndex &parent) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex& parent) override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    void setQuery(const cvar::VariantQuery& q);

    QSqlRecord record(const QModelIndex& index);

    const cvar::VariantQuery& currentQuery() const;

    bool exportCsv(const QString& filename) const;

    bool isEmpty() const;


public Q_SLOTS:
    void load();
    void load(int offset, int limit);


private:
    cvar::VariantQuery mCurrentQuery;
    QList<QSqlRecord> mRecords;
    QHash<int, QList<QSqlRecord>> mChilds;
    int mTotalRowCount = 0;


};

#endif // RESULTTREEMODEL_H
