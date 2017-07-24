#include "resultmodel.h"
namespace core {
ResultModel::ResultModel(Project * prj, QObject *parent)
{
    mProject = prj;
}

void ResultModel::setQuery(const QString &raw)
{
    clear();

    mProject->sqliteManager()->queryBuilder()->setFromRaw(raw);
    QString q = mProject->sqliteManager()->queryBuilder()->toSql();

    QSqlQuery query;
    query.exec(q);

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
                // add Here sub child
            }


        }

        appendRow(row);
    }
}
}
