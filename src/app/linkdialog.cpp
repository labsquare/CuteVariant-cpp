#include "linkdialog.h"

LinkDialog::LinkDialog(QWidget *parent)
    :QDialog(parent)
{

    mView       = new QListWidget();
    mAddButton  = new QPushButton(tr("Add"));
    mRemButton  = new QPushButton(tr("Rem"));
    mQuitButton = new QPushButton(tr("Cancel"));


    QVBoxLayout * buttonLayout  = new QVBoxLayout();
    buttonLayout->addWidget(mAddButton);
    buttonLayout->addWidget(mRemButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(mQuitButton);

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(mAddButton, &QPushButton::clicked, this, &LinkDialog::addLink);
    connect(mRemButton, &QPushButton::clicked, this, &LinkDialog::remLink);
    connect(mQuitButton, &QPushButton::clicked, this, &LinkDialog::reject);

}

void LinkDialog::addLink()
{




}

void LinkDialog::remLink()
{

}
