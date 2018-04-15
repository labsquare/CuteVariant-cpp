#include "beddockwidget.h"

BedDockWidget::BedDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    setTitle("Bed");

    mView = new QTreeWidget;
    mView->header()->hide();

    setWidget(mView);


    addAction(FIcon(0xf1ba), "Import bed", this, SLOT(addBedFile()));

    addActionSpacer();

    addAction(FIcon(0xf5e8), "Remove all", this, SLOT(addBedFile()));


    connect(mView, &QTreeWidget::doubleClicked, this, &BedDockWidget::changed);

}

void BedDockWidget::reset()
{
    mView->clear();

    for (cvar::BedFile file : cutevariant->sqlite()->bedFiles())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0, file.filename());
        item->setText(1, QString::number(file.count()));
        mView->addTopLevelItem(item);
    }

}

QString BedDockWidget::region() const
{
    if (mView->selectedItems().size() > 0)
        return mView->currentItem()->text(0);

    return QString();
}

void BedDockWidget::addBedFile()
{

    QString filename = QFileDialog::getOpenFileName(this);

    if (filename.isEmpty())
        return ;

    qDebug()<<cutevariant->sqlite()->importBedfile(filename);

    reset();


}
