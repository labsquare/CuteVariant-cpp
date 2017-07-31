#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H
#include <QtWidgets>
#include <QFutureWatcher>
#include "project.h"

class ImportDialog : public QDialog
{
    Q_OBJECT
public:
    ImportDialog( cvar::Project * prj);
    void setFilename(const QString& file);

    virtual int exec() override;


protected Q_SLOTS:
    void updateStep(int progress, const QString& message);
    void importFinished();

private:
    cvar::Project * mPrj;
    QProgressBar * mBar;
    QPlainTextEdit * mEdit;
    QDialogButtonBox * mButtonBox;
    QFutureWatcher<bool> mWatcher;
    QString mFilename;
};

#endif // IMPORTDIALOG_H
