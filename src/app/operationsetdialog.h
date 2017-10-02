#ifndef OPERATIONSETDIALOG_H
#define OPERATIONSETDIALOG_H
#include <QtWidgets>
#include "qfonticon.h"
#include "project.h"
#include "sqlitemanager.h"

class OperationSetDialog : public QDialog
{
public:
    OperationSetDialog(QWidget * parent = nullptr);
    QString expression() const;
    QString tableName() const;

    cvar::SqliteManager::CompareMode mode() const;

protected:
    void load();


private:
    QComboBox * mModeBox;
    QLineEdit * mNewName;
    QComboBox * mBoxA;
    QComboBox * mBoxB;
    QComboBox * mOperator;



};

#endif // OPERATIONSETDIALOG_H
