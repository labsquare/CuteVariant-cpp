#include "columnmodel.h"

ColumnModel::ColumnModel( QObject *parent)
    :QStandardItemModel(parent)
{

    //load();

    connect(this,SIGNAL(itemChanged(QStandardItem*)),
            this,SLOT(itemCheckChanged(QStandardItem*)));





}

void ColumnModel::load()
{
    qDebug()<<Q_FUNC_INFO<<"load ";
    clear();
    setColumnCount(1);
    mCategoriesItems.clear();
    for (cvar::Field f : cutevariant->sqliteManager()->fields())
    {
        // create category
        if (!mCategoriesItems.contains(f.category())){
            mCategoriesItems[f.category()] = new QStandardItem(f.category().toLower());
            mCategoriesItems[f.category()]->setCheckable(true);
        }

        // append item to category
        mCategoriesItems[f.category()]->appendRow(createItem(f.name().toLower(),f.description(),f.colname()));
    }


    // insert all annotation (variant first)
    QStringList keys = mCategoriesItems.keys();
    std::reverse(keys.begin(), keys.end());
    for (QString key : keys)
        appendRow(mCategoriesItems[key]);



    // add Samples
    mSampleItem = createItem("samples", "fields of samples");

    if (!cutevariant->sqliteManager()->samples().isEmpty())
    {
        for (cvar::Sample s : cutevariant->sqliteManager()->samples())
        {
            QStandardItem * c1 = createItem(s.name(), "Sample name", s.name());
            mSampleItem->appendRow(c1);

            for (cvar::Field f : cutevariant->sqliteManager()->genotypeFields())
            {
                // TODO : check how colname are saved ...
                QStandardItem * g = createItem(f.name(), f.description(),f.name());
                c1->appendRow(g);
            }
        }
        appendRow(mSampleItem);
    }
}
//---------------------------------------------------------
QStringList ColumnModel::selectedColumns() const
{
    // get columns variants
    QStringList columns;

    // Get selected items
    QStringList keys = mCategoriesItems.keys();
    std::reverse(keys.begin(), keys.end());
    for (QString key : keys)
    {
        QStandardItem * item = mCategoriesItems[key];
        for (int i=0; i< item->rowCount(); ++i)
        {
            if (item->child(i)->checkState() == Qt::Checked){
                columns.append(QString("%1.%2").arg(item->text(),item->child(i)->text()));

            }
        }
    }

    // Get selected sampled
    for (int i=0; i<mSampleItem->rowCount(); ++i)
    {
        QString sample = mSampleItem->child(i)->data().toString();
        for (int j=0; j < mSampleItem->child(i)->rowCount(); ++j)
        {
            if (mSampleItem->child(i)->child(j)->checkState() == Qt::Checked)
                columns.append(QString("sample[\"%1\"].%2").arg(sample).arg(mSampleItem->child(i)->child(j)->data().toString()));
        }
    }


    return columns;



}
//---------------------------------------------------------
void ColumnModel::itemCheckChanged(QStandardItem *item)
{
    for (int row = 0; row < item->rowCount(); ++row)
    {
        item->child(row)->setCheckState(item->checkState());
    }

    qDebug()<<selectedColumns();

}
//---------------------------------------------------------
QStandardItem *ColumnModel::createItem(const QString &name, const QString &description, const QString &colname)
{
    QStandardItem * item = new QStandardItem(name);
    item->setToolTip(description);
    item->setCheckable(true);
    item->setEditable(false);



    item->setData(colname);


    return item;
}
//---------------------------------------------------------

