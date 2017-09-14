#include "linklistdialog.h"

LinkListDialog::LinkListDialog(QWidget *parent)
    :QDialog(parent)
{

    mView       = new QTreeWidget();
    mAddButton  = new QPushButton(tr("Add"));
    mEditButton = new QPushButton(tr("Edit"));
    mRemButton  = new QPushButton(tr("Rem"));
    mQuitButton = new QPushButton(tr("Cancel"));


    QVBoxLayout * buttonLayout  = new QVBoxLayout();
    buttonLayout->addWidget(mAddButton);
    buttonLayout->addWidget(mEditButton);
    buttonLayout->addWidget(mRemButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(mQuitButton);

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(mAddButton, &QPushButton::clicked, this, &LinkListDialog::addLink);
    connect(mRemButton, &QPushButton::clicked, this, &LinkListDialog::remLink);
    connect(mEditButton, &QPushButton::clicked, this, &LinkListDialog::editLink);

    connect(mQuitButton, &QPushButton::clicked, this, &LinkListDialog::reject);

    load();

}

void LinkListDialog::addLink()
{
    EditLinkDialog dialog(this);

    if (dialog.exec())
    {
        cvar::VariantLink link = dialog.link();
        if (!cutevariant->sqliteManager()->saveLink(link))
            QMessageBox::warning(this,"error","Cannot save links");

        else
            load();

    }
}

void LinkListDialog::remLink()
{

    if (mView->selectedItems().isEmpty())
        return;

    if (!cutevariant->sqliteManager()->removeLink(mLinks[mView->currentIndex().row()]))
        QMessageBox::warning(this,"error","Cannot delete item");

    else
        load();


}

void LinkListDialog::editLink()
{

    if (mView->selectedItems().isEmpty())
        return;

    EditLinkDialog dialog(this);
    dialog.setLink(mLinks[mView->currentIndex().row()]);

    if (dialog.exec())
    {
        cvar::VariantLink link = dialog.link();

        qDebug()<<"MY ID "<<link.id();

        if (!cutevariant->sqliteManager()->saveLink(link))
            QMessageBox::warning(this,"error","Cannot save links");

        else
            load();

    }


}

void LinkListDialog::load()
{

    mView->clear();
    mView->setColumnCount(2);

    mLinks = cutevariant->sqliteManager()->links();

    for (cvar::VariantLink link : mLinks)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setIcon(0, link.icon());
        item->setText(0, link.name());
        item->setText(1, link.url());

        mView->addTopLevelItem(item);

    }

    mView->header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    mView->setIconSize(QSize(32,32));

    mView->header()->setStretchLastSection(true);


}
