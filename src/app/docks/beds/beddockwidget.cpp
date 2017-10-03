#include "beddockwidget.h"

BedDockWidget::BedDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    setTitle("Bed");

    mView = new QTreeWidget;

    setWidget(mView);


    addAction(QIcon(), "Import bed", this, SLOT(addBedFile()));

}

void BedDockWidget::reset()
{
    mView->clear();

    for (cvar::BedFile file : cutevariant->sqliteManager()->bedFiles())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0, file.filename());
        item->setText(1, QString::number(file.count()));
        mView->addTopLevelItem(item);
    }

}

void BedDockWidget::addBedFile()
{

    QString filename = QFileDialog::getOpenFileName(this);

    if (filename.isEmpty())
        return ;

    qDebug()<<cutevariant->sqliteManager()->importBedfile(filename);

    reset();


}
