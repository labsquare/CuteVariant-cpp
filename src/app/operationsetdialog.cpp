#include "operationsetdialog.h"

OperationSetDialog::OperationSetDialog(QWidget *parent)
    :QDialog(parent)
{

    mModeBox  = new QComboBox;
    mExprEdit = new QPlainTextEdit;

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QFormLayout * formLayout = new QFormLayout;

    formLayout->addRow("Mode",mModeBox);
    formLayout->addRow("Expression",mExprEdit);

    mModeBox->addItem("Site (chr,pos)");
    mModeBox->addItem("Variant (chr,pos, ref, alt)");

    QVBoxLayout * mainLayout = new QVBoxLayout;

    mainLayout->addLayout(formLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


}

QString OperationSetDialog::expression() const
{
    return mExprEdit->toPlainText();
}


