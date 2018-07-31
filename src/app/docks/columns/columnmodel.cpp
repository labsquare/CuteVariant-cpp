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
    mFieldItems.clear();
    mOrderCategories.clear();
    mCategoriesItems.clear();

    clear();
    setColumnCount(1);

    // Create categories
    for (cvar::Field f : cutevariant->fields())
    {
        // create category if not exists
        if (!mCategoriesItems.contains(f.category())){
            mCategoriesItems[f.category()] = createCategory(f.category().toLower());
            mOrderCategories.append(f.category());
        }
        // append item to category
        mCategoriesItems[f.category()]->appendRow(createField(f));
    }


    // append categories
    for (QString key : mOrderCategories)
        appendRow(mCategoriesItems[key]);


    // add Samples
    QStandardItem * sampleCategorie = createCategory("Samples", "All samples avaibles");
    sampleCategorie->setIcon(FIcon(0xf00e));

    if (!cutevariant->samples().isEmpty())
    {
        for (cvar::Sample s : cutevariant->samples())
        {
            QStandardItem * c1 = createCategory(s.name().toUpper());
            c1->setIcon(FIcon(0xf004));
            sampleCategorie->appendRow(c1);

            for (cvar::Field f : cutevariant->genotypeFields())
            {
                // TODO : check how colname are saved ...
                QStandardItem * g = createField(f);
                c1->appendRow(g);
            }
        }
        appendRow(sampleCategorie);
    }


    // check default variants

    for (QModelIndex& i : match(index(0,0), Qt::DisplayRole, "(favoris|pos|chr|pos|alt)",10,Qt::MatchRecursive|Qt::MatchRegExp))
    {
          itemFromIndex(i)->setCheckState(Qt::Checked);
    }



}
//---------------------------------------------------------
QStringList ColumnModel::selectedColumns() const
{
    // get columns variants
    // TODO Make it better, this is useless ....

    QStringList columns;

    for ( auto it : mFieldItems)
    {
        if (it.first->checkState() == Qt::Checked)
        {
            columns.append(it.second.expression());
        }

    }
    return columns;
}
//---------------------------------------------------------
QList<cvar::Field> ColumnModel::selectedFields() const
{
    QList<cvar::Field> fields;
    for (auto it : mFieldItems)
    {
        if (it.first->checkState() == Qt::Checked)
        {
            fields.append(it.second);
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


    for (auto it : mFieldItems)
    {
        if (it.first == item)
            return it.second;
    }

    return cvar::Field();

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
    item->setIcon(FIcon(0xf256));
    return item;
}
//---------------------------------------------------------
QStandardItem *ColumnModel::createField(const cvar::Field &field)
{
    QStandardItem * item = new QStandardItem(field.name());
    item->setToolTip(field.description());
    item->setCheckable(mHasCheckbox);
    item->setEditable(false);
    mFieldItems.append(qMakePair(item,field));

    if (field.type() == cvar::Field::INTEGER)
        item->setIcon(FIconColor(0xf23b,QColor("#EA9F37")));

    if (field.type() == cvar::Field::TEXT)
        item->setIcon(FIconColor(0xf23b,QColor("#4183B0")));

    if (field.type() == cvar::Field::BOOL)
        item->setIcon(FIconColor(0xf23b,QColor("#EF2929")));

    if (field.type() == cvar::Field::REAL)
        item->setIcon(FIconColor(0xf23b,QColor("#A1C97A")));


    return item;
}
//---------------------------------------------------------


