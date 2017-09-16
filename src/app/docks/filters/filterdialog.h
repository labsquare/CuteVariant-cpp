#ifndef CONDITIONDIALOG_H
#define CONDITIONDIALOG_H
#include <QtWidgets>
#include "project.h"

#include "annotationconditionpage.h"
#include "genotypeconditionpage.h"
#include "filteritem.h"


class FilterDialog : public QDialog
{
public:
    FilterDialog(QWidget * parent = nullptr);
    void addWidget(QWidget * w);


    FilterItem * toItem();
    void fromItem(FilterItem * item);


private:
    QDialogButtonBox * mBox;
    QTabWidget * mTabWidget;

};

#endif // CONDITIONDIALOG_H
