#ifndef LOCATIONLINEEDIT_H
#define LOCATIONLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include "project.h"
class LocationLineEdit : public QLineEdit
{
public:
    LocationLineEdit(cvar::Project * prj, QWidget * parent = nullptr);


private:
    cvar::Project * mPrj;
};

#endif // LOCATIONLINEEDIT_H
