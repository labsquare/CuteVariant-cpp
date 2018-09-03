#include "editlinkdialog.h"

EditLinkDialog::EditLinkDialog(QWidget *parent)
    :QDialog(parent)
{

    mNameEdit   = new QLineEdit();
    mUrlEdit   = new QLineEdit();
    miconButton = new QToolButton();

    miconButton->setMinimumSize(32,32);

    QDialogButtonBox * buttonBox  = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

    QFormLayout * formLayout = new QFormLayout;
    formLayout->addRow("Icon", miconButton);
    formLayout->addRow("Name", mNameEdit);
    formLayout->addRow("Url",mUrlEdit);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    connect(miconButton, &QToolButton::clicked, this, &EditLinkDialog::changeIcon);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditLinkDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditLinkDialog::reject);


}

void EditLinkDialog::setLink(const cvar::VariantLink &link)
{
//    mCurrentLink = link;
//    mNameEdit->setText(link.name());
//    mUrlEdit->setText(link.rawUrl());
//    miconButton->setIcon(link.icon());
}

const cvar::VariantLink &EditLinkDialog::link()
{
//    mCurrentLink.setName(mNameEdit->text());
//    mCurrentLink.setRawUrl(mUrlEdit->text());
//    mCurrentLink.setIcon(miconButton->icon());

//    return mCurrentLink;
}


void EditLinkDialog::changeIcon()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), QDir::home().path(),tr("Images (*.png *.xpm *.jpg)"));
    QPixmap pix(fileName);
    miconButton->setIcon(QIcon(pix.scaled(32,32)));

}
