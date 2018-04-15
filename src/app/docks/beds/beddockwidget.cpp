#include "beddockwidget.h"

RegionDockWidget::RegionDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    setTitle("Region");

    mView = new QTreeWidget;
    mView->header()->hide();
    mView->setIndentation(0);
    mView->setIconSize(QSize(22,22));

    setWidget(mView);


    addAction(FIcon(0xf1ba), "Import bed", this, SLOT(addBedFile()));

    addActionSpacer();

    addAction(FIcon(0xf5e8), "Remove all", this, SLOT(addBedFile()));


    connect(mView, &QTreeWidget::doubleClicked, this, &RegionDockWidget::changed);

}

void RegionDockWidget::reset()
{
    mView->clear();

    for (cvar::BedFile file : cutevariant->sqlite()->bedFiles())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setIcon(0,FIcon(0xf214));
        item->setText(0, file.filename());
        item->setText(1, QString::number(file.count()));
        mView->addTopLevelItem(item);
    }

}

QString RegionDockWidget::region() const
{
    if (mView->selectedItems().size() > 0)
        return mView->currentItem()->text(0);

    return QString();
}

void RegionDockWidget::addBedFile()
{

    QString filename = QFileDialog::getOpenFileName(this);

    if (filename.isEmpty())
        return ;

    qDebug()<<cutevariant->sqlite()->importBedfile(filename);

    reset();


}
