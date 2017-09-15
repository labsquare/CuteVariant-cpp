#ifndef OPERATIONSETDIALOG_H
#define OPERATIONSETDIALOG_H
#include <QtWidgets>
#include "project.h"

class OperationSetDialog : public QDialog
{
public:
    OperationSetDialog(QWidget * parent = nullptr);
    QString expression() const;



private:
    QComboBox * mModeBox;
    QPlainTextEdit * mExprEdit;


};

#endif // OPERATIONSETDIALOG_H
