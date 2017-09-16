#ifndef OPERATIONSETDIALOG_H
#define OPERATIONSETDIALOG_H
#include <QtWidgets>
#include "project.h"
#include "sqlitemanager.h"

class OperationSetDialog : public QDialog
{
public:
    OperationSetDialog(QWidget * parent = nullptr);
    QString expression() const;
    QString tableName() const;

    cvar::SqliteManager::CompareMode mode() const;



private:
    QComboBox * mModeBox;
    QLineEdit * mNewName;
    QPlainTextEdit * mExprEdit;


};

#endif // OPERATIONSETDIALOG_H
