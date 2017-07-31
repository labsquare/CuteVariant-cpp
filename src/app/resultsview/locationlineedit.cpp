#include "locationlineedit.h"

LocationLineEdit::LocationLineEdit(cvar::Project *prj, QWidget *parent)
    :QLineEdit(parent)
{
    mPrj = prj;
    setPlaceholderText("<chr>:<position>");


}
