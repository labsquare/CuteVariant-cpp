#include "importfilepage.h"

ImportFilePage::ImportFilePage(QWidget *parent)
    :QWizardPage(parent)
{

    setTitle("Select a file to import");
    setSubTitle("Could be raw vcf or annotated vcf with snpEff or Vep");

    QFormLayout * mainLayout = new QFormLayout;

    mFileEdit        = new FileEditWidget();
    mPedFileEdit     = new FileEditWidget();
    mUnlockButton    = new QPushButton(tr("unlock"));
    mFormatBox       = new QComboBox();

    mPedFileEdit->edit()->setPlaceholderText(tr("Not required"));


    QHBoxLayout * formatLayout = new QHBoxLayout;
    formatLayout->addWidget(mFormatBox);
    formatLayout->addWidget(mUnlockButton);

    mFormatBox->setEnabled(false);

    mainLayout->addRow(tr("Filename"), mFileEdit);
    //mainLayout->addRow(tr("pedfile"), mPedFileEdit);

    mainLayout->addRow(tr("Format detected"), formatLayout);

    mFormatBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    connect(mUnlockButton,&QPushButton::clicked, [this](){mFormatBox->setEnabled(true);});
    connect(mFileEdit->edit(), &QLineEdit::textChanged, this, &ImportFilePage::checkFile);

    setLayout(mainLayout);


    registerField("filename", mFileEdit->edit(), "text");
    registerField("format", mFormatBox, "currentData");


    // fill combobox

    mFormatBox->clear();



//    QMetaEnum metaEnum = QMetaEnum::fromType<cvar::VariantReaderFactory::Format>();

//    for (int i=0; i< metaEnum.keyCount();  ++i)
//    {
//        mFormatBox->addItem(metaEnum.valueToKey(i), metaEnum.value(i));
//    }

}

bool ImportFilePage::isComplete() const
{
    QString filename = mFileEdit->text();
    return QFile::exists(filename);
}

void ImportFilePage::checkFile()
{
    QString filename = mFileEdit->text();

    if (!filename.isEmpty()){

        QString dbFile = filename + ".db";

        if (QFile::exists(dbFile))
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Warning);
            box.setText(tr("There is already a db file with the same name in this location"));
            box.setInformativeText(tr("Do you want to remove the file ?"));
            box.setWindowTitle(dbFile);
            box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);

            if (box.exec() == QMessageBox::Yes)
            {
                QFile file(dbFile);
                if (!file.remove())
                    QMessageBox::warning(this,dbFile,tr("Cannot remove file"));


            }

            else
                return;


        }
        detectFormat();
        emit completeChanged();
    }
}


void ImportFilePage::detectFormat()
{

//    QFile file(mFileEdit->text());
//    cvar::VariantReaderFactory::Format format;

//    if (cvar::VariantReaderFactory::isGzip(&file))
//    {
//        auto * gzip = new KCompressionDevice(&file,false, KCompressionDevice::GZip);
//        format = cvar::VariantReaderFactory::detectFormat(gzip);
//        delete gzip;
//    }

//    else
//        format = cvar::VariantReaderFactory::detectFormat(&file);



//    mFormatBox->setCurrentIndex(mFormatBox->findData(format));





}
