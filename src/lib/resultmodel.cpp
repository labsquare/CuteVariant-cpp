#include "resultmodel.h"
namespace core {
ResultModel::ResultModel(QObject *parent)
{

}

void ResultModel::setProject(Project *prj)
{
    mProject = prj;
}

void ResultModel::setQuery(const QString &raw)
{
    clear();

    qDebug()<<mProject->sqliteManager()->buildVariantQuery(raw);


//    qDebug()<<query.lastQuery();
//    qDebug()<<query.lastError().text();


//    setColumnCount(query.record().count());

//    QStringList header;
//    for (int i=0; i<query.record().count(); ++i)
//        header.append(query.record().field(i).name());

//    setHorizontalHeaderLabels(header);

//    while (query.next())
//    {
//        QList<QStandardItem*> row ;
//        for (int i=0; i<query.record().count(); ++i)
//        {
//            QStandardItem * item = new QStandardItem();
//            item->setText(query.record().value(i).toString());
//            row.append(item);

//            if (i==0){

//                item->setCheckable(true);
//                // add Here sub child
//            }


//        }

//        appendRow(row);

//    }




}
}
