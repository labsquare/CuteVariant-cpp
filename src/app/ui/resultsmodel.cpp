#include "resultsmodel.h"
ResultsModel::ResultsModel(core::Project * prj, QObject *parent)
    :QStandardItemModel(parent)
{
    mProject = prj;
}

void ResultsModel::setQuery(const QString &raw)
{
    clear();
    mProject->sqliteManager()->queryBuilder()->setFromRaw(raw);
    load();
}

int ResultsModel::variantCount() const
{
    return mProject->sqliteManager()->variantQueryCount();

}

void ResultsModel::load()
{
    clear();
    QSqlQuery query = mProject->sqliteManager()->variantQuery();

    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();

    setColumnCount(query.record().count());

    QStringList header;
    for (int i=0; i<query.record().count(); ++i)
        header.append(query.record().field(i).name());

    setHorizontalHeaderLabels(header);

    while (query.next())
    {
        QList<QStandardItem*> row ;
        for (int i=0; i<query.record().count(); ++i)
        {
            QStandardItem * item = new QStandardItem();
            item->setText(query.record().value(i).toString());
            row.append(item);

            if (i==0){

                item->setCheckable(true);

                item->setRowCount(10);

                // add Here sub child
            }
        }

        appendRow(row);
    }
}

