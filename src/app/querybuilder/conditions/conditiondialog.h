#ifndef CONDITIONDIALOG_H
#define CONDITIONDIALOG_H
#include <QtWidgets>
#include "condannwidget.h"
#include "project.h"

class ConditionDialog : public QDialog
{
public:
    ConditionDialog(cvar::Project * prj, QWidget * parent = nullptr);
    void addWidget(QWidget * w);

protected:



private:
    QDialogButtonBox * mBox;
    QTabWidget * mTabWidget;
    cvar::Project * mPrj;

};

#endif // CONDITIONDIALOG_H
