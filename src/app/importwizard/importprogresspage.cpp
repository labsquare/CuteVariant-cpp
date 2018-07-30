#include "importprogresspage.h"

ImportProgressPage::ImportProgressPage(QWidget * parent)
    :QWizardPage(parent)
{

setTitle("Create sqlite database");
setSubTitle("Press start to import file. It can takes a while");


mTabWidget   = new QTabWidget;
mMsgEdit     = new QPlainTextEdit;
mBar         = new QProgressBar;
mStartButton = new QPushButton(tr("Import"));

mTabWidget->addTab(mMsgEdit, tr("Messages"));
QVBoxLayout * mainLayout = new QVBoxLayout;
QHBoxLayout * barLayout = new QHBoxLayout;
barLayout->addWidget(mBar);
barLayout->addWidget(mStartButton);

mainLayout->addLayout(barLayout);
mainLayout->addWidget(mTabWidget);

mMsgEdit->setFrameShape(QFrame::NoFrame);
setLayout(mainLayout);
setCommitPage(true);
setButtonText(QWizard::CommitButton, tr("Next"));


setButtonText(QWizard::CustomButton1, "Import");

connect(mStartButton,&QPushButton::clicked,this, &ImportProgressPage::importFile);

connect(cutevariant->sqlite(),SIGNAL(importProgressChanged(int,QString)),
        this,SLOT(updateStep(int,QString)));

connect(cutevariant->sqlite(),SIGNAL(importRangeChanged(int,int)),
        mBar,SLOT(setRange(int,int)));

connect(&mWatcher,SIGNAL(finished()), this,SLOT(importFinished()));


}

void ImportProgressPage::importFile()
{

QString filename = field("filename").toString();
auto format = cvar::VariantReaderFactory::Format (field("format").toInt());

QFuture<bool> future = cutevariant->sqlite()->asyncImportFile(filename, format);
mWatcher.setFuture(future);


}



void ImportProgressPage::initializePage()
{
 mMsgEdit->clear();

}

bool ImportProgressPage::validatePage()
{
    return true;
}

bool ImportProgressPage::isComplete() const
{
    return mDone;
}

void ImportProgressPage::updateStep(int progress, const QString &message)
{
    mBar->setValue(progress);

    if (!message.isEmpty())
        mMsgEdit->appendPlainText(message);
}

void ImportProgressPage::importFinished()
{

    if (!mWatcher.future().result())
    {
        QMessageBox::warning(this,"erreur","cannot import the file");
        close();
    }

    mDone = true;
    emit completeChanged();

}
