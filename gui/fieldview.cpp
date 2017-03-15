#include "fieldview.h"

FieldView::FieldView(QWidget *parent)
    :QTreeWidget(parent)
{
    setColumnCount(2);
}

QStringList FieldView::selectedColNames() const
{
    QStringList colnames;
    for (int i=0; i<topLevelItemCount(); ++i)
    {
        if (topLevelItem(i)->checkState(0) == Qt::Checked)
        {
            colnames.append(topLevelItem(i)->text(0));
        }
    }

    qDebug()<<colnames;
    return colnames;

}

void FieldView::refresh()
{
    clear();
    for (Field f : Project::fields())
    {

        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0, f.name());
        item->setText(1, f.description());
        item->setCheckState(0,Qt::Unchecked);
        addTopLevelItem(item);

    }

}
