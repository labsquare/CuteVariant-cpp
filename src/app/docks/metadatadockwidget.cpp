#include "metadatadockwidget.h"

MetadataDockWidget::MetadataDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{
    mView = new QTreeWidget;
    mView->setAlternatingRowColors(true);
    setWidget(mView);

    setTitle("File metadata");


}

void MetadataDockWidget::reset()
{
    mView->clear();
    mView->setColumnCount(2);
    mView->setHeaderLabels({"key", "value"});

    QHash<QString, QVariant> metadatas = cutevariant->sqliteManager()->metadatas();

    for (auto it = metadatas.begin(); it != metadatas.end(); ++it)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0,it.key());
        item->setText(1,it.value().toString());

        mView->addTopLevelItem(item);
    }
}
