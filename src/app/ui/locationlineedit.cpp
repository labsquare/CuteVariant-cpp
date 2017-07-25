#include "locationlineedit.h"

LocationLineEdit::LocationLineEdit(core::Project *prj, QWidget *parent)
    :QLineEdit(parent)
{
    mPrj = prj;
    setPlaceholderText("<chr>:<position>");


}
