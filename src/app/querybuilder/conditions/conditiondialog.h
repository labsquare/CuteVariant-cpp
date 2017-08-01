#ifndef CONDITIONDIALOG_H
#define CONDITIONDIALOG_H
#include <QtWidgets>
#include "project.h"

#include "annotationconditionpage.h"
#include "genotypeconditionpage.h"


class ConditionDialog : public QDialog
{
public:
    ConditionDialog(QWidget * parent = nullptr);
    void addWidget(QWidget * w);

protected:

private:
    QDialogButtonBox * mBox;
    QTabWidget * mTabWidget;

};

#endif // CONDITIONDIALOG_H
