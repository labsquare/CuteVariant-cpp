#include "operationsetdialog.h"

OperationSetDialog::OperationSetDialog(QWidget *parent)
    :QDialog(parent)
{

    mModeBox  = new QComboBox;
    mNewName  = new QLineEdit;
    mBoxA     = new QComboBox;
    mBoxB     = new QComboBox;
    mOperator = new QComboBox;

    mNewName->setPlaceholderText("Name ...");

    mOperator->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QVBoxLayout * formLayout = new QVBoxLayout;

    formLayout->addWidget(mNewName);
    formLayout->addWidget(mModeBox);

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mBoxA);
    hLayout->addWidget(mOperator);
    hLayout->addWidget(mBoxB);

    formLayout->addLayout(hLayout);

    QVBoxLayout * mainLayout = new QVBoxLayout;

    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


    load();

}

QString OperationSetDialog::expression() const
{
    return mBoxA->currentText() + mOperator->currentData().toString() + mBoxB->currentText();
}

QString OperationSetDialog::tableName() const
{
    return mNewName->text();
}

cvar::SqliteManager::CompareMode OperationSetDialog::mode() const
{
    if (mModeBox->currentIndex() == 0)
        return cvar::SqliteManager::SiteMode;

    if (mModeBox->currentIndex() == 1)
        return cvar::SqliteManager::VariantMode;

    return cvar::SqliteManager::SiteMode;

}

void OperationSetDialog::load()
{

    mBoxA->clear();
    mBoxB->clear();
    mOperator->clear();

    mModeBox->addItem("By Site chr,pos)", cvar::SqliteManager::SiteMode);
    mModeBox->addItem("By variant (chr,pos, ref, alt)", cvar::SqliteManager::VariantMode);

    mOperator->addItem(FIcon(0xf564), "Union", "+");
    mOperator->addItem(FIcon(0xf55d),"Intersect","&");
    mOperator->addItem(FIcon(0xf55c),"Subtract","-");


    for (const QString& name : cutevariant->sqlite()->variantSetNames())
    {
        mBoxA->addItem(name);
        mBoxB->addItem(name);
    }



}


