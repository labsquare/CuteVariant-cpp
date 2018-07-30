#ifndef IMPORTFILEPAGE_H
#define IMPORTFILEPAGE_H
#include <QWizardPage>
#include <QtWidgets>
#include "variantreaderfactory.h"

class ImportFilePage : public QWizardPage
{
public:
    ImportFilePage(QWidget * parent = nullptr);


protected Q_SLOTS:
    void browse();
    void detectFormat();

private:
    QLineEdit * mFileEdit;
    QPushButton * mBrowseButton;
    QPushButton * mUnlockButton;
    QComboBox * mFormatBox;


};

#endif // IMPORTFILEPAGE_H
