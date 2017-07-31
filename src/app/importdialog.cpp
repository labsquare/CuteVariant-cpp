#include "importdialog.h"

ImportDialog::ImportDialog(cvar::Project *prj)
    :QDialog(), mPrj(prj)
{

    mBar = new QProgressBar;
    mEdit = new QPlainTextEdit;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
    mEdit->setReadOnly(true);

    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(mBar);
    layout->addWidget(mEdit);
    layout->addWidget(mButtonBox);
    setLayout(layout);

    connect(mPrj->sqliteManager(),SIGNAL(importProgressChanged(int,QString)),
            this,SLOT(updateStep(int,QString)));

    connect(mPrj->sqliteManager(),SIGNAL(importRangeChanged(int,int)),
            mBar,SLOT(setRange(int,int)));

    connect(mButtonBox, SIGNAL(rejected()), this,SLOT(reject()));
    connect(mButtonBox, SIGNAL(accepted()), this,SLOT(accept()));

    connect(&mWatcher,SIGNAL(finished()), this,SLOT(importFinished()));


}

void ImportDialog::setFilename(const QString &file)
{
    mFilename = file;
}

int ImportDialog::exec()
{
    QFuture<bool> future = mPrj->sqliteManager()->asyncImportFile(mFilename);
    mWatcher.setFuture(future);

    if (QDialog::exec() == QDialog::Rejected)
    {
        mWatcher.cancel();
        mWatcher.waitForFinished();
        return QDialog::Rejected;
    }



    return QDialog::Accepted;
}



void ImportDialog::updateStep(int progress, const QString &message)
{
    mBar->setValue(progress);

    if (!message.isEmpty())
        mEdit->appendPlainText(message);
}

void ImportDialog::importFinished()
{

    mButtonBox->addButton(QDialogButtonBox::Ok);

}
