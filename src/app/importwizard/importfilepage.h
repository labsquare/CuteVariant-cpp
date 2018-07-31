#ifndef IMPORTFILEPAGE_H
#define IMPORTFILEPAGE_H
#include <QWizardPage>
#include <QtWidgets>
#include "variantreaderfactory.h"
#include "kcompressiondevice.h"
#include "fileeditwidget.h"

class ImportFilePage : public QWizardPage
{
public:
    ImportFilePage(QWidget * parent = nullptr);


    virtual bool isComplete() const override;

public Q_SLOTS:
    void checkFile();


protected Q_SLOTS:
    void detectFormat();

private:
    FileEditWidget * mFileEdit;
    QPushButton * mUnlockButton;
    QComboBox * mFormatBox;
    FileEditWidget * mPedFileEdit;




};

#endif // IMPORTFILEPAGE_H
