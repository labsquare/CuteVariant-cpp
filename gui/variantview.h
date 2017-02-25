#ifndef VARIANTVIEW_H
#define VARIANTVIEW_H
#include <QtWidgets>
#include <QtCore>
#include "variantmodel.h"

class VariantView : public QTableView
{
public:
    VariantView(QWidget * parent = 0);

    void setAnnotationColumns(const QStringList& colnames);
    void update();

private:
    VariantModel * mModel;
};

#endif // VARIANTVIEW_H
