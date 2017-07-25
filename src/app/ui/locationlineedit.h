#ifndef LOCATIONLINEEDIT_H
#define LOCATIONLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include "project.h"
class LocationLineEdit : public QLineEdit
{
public:
    LocationLineEdit(core::Project * prj, QWidget * parent = nullptr);


private:
    core::Project * mPrj;
};

#endif // LOCATIONLINEEDIT_H
