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
    for (cvar::Field f : cutevariant->sqliteManager()->fields())
    {
        // create category if not exists
        if (!mCategoriesItems.contains(f.category()))
            mCategoriesItems[f.category()] = createCategory(f.category().toLower());

        // append item to category
        mCategoriesItems[f.category()]->appendRow(createField(f, QString("%1.%2").arg(f.category().toLower(),f.name())));
    }


    // ODERING insert all annotation (variant first)
    QStringList keys = mCategoriesItems.keys();
    std::reverse(keys.begin(), keys.end());
    for (QString key : keys)
        appendRow(mCategoriesItems[key]);


    // add Samples
    mSampleItem = createCategory("Samples", "All samples avaibles");

    if (!cutevariant->sqliteManager()->samples().isEmpty())
    {
        for (cvar::Sample s : cutevariant->sqliteManager()->samples())
        {
            QStandardItem * c1 = createCategory(s.name().toUpper());
            mSampleItem->appendRow(c1);

            for (cvar::Field f : cutevariant->sqliteManager()->genotypeFields())
            {
                // TODO : check how colname are saved ...
                QStandardItem * g = createField(f, QString("sample[\"%1\"].%2").arg(s.name(), f.name()));
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
    // TODO Make it better, this is useless ....

    QStringList columns;

    for ( QStandardItem * item : mFieldItems.keys())
    {
        if (item->checkState() == Qt::Checked)
        {
            columns.append(item->data().toString());
        }

    }

    return columns;


}
//---------------------------------------------------------
QList<cvar::Field> ColumnModel::selectedFields() const
{
    QList<cvar::Field> fields;
    for ( QStandardItem * item : mFieldItems.keys())
    {
        if (item->checkState() == Qt::Checked)
        {
            fields.append(mFieldItems[item]);
        }

    }
    return fields;
}
//---------------------------------------------------------
const cvar::Field ColumnModel::field(const QModelIndex &index) const
{
    QStandardItem * item = itemFromIndex(index);
    if (!item)
        return cvar::Field();

    if (!mFieldItems.contains(item))
        return cvar::Field();

    return mFieldItems[item];

}
//---------------------------------------------------------
void ColumnModel::setCheckBox(bool enabled)
{
        mHasCheckbox = enabled;

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
QStandardItem *ColumnModel::createCategory(const QString &name, const QString &description)
{
    QStandardItem * item = new QStandardItem(name);
    item->setToolTip(description);
    item->setCheckable(mHasCheckbox);
    item->setEditable(false);
    return item;
}
//---------------------------------------------------------
QStandardItem *ColumnModel::createField(const cvar::Field &field, const QString &vql)
{
    QStandardItem * item = new QStandardItem(field.name());
    item->setToolTip(field.description());
    item->setCheckable(mHasCheckbox);
    item->setEditable(false);
    item->setData(vql);
    mFieldItems[item] = field;
    return item;
}
//---------------------------------------------------------


