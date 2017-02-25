#include "variantview.h"

VariantView::VariantView(QWidget *parent)
    :QTableView(parent)
{
    mModel = new VariantModel;
    setModel(mModel);




}

void VariantView::setAnnotationColumns(const QStringList &colnames)
{
    mModel->setAnnotationColumns(colnames);
}

void VariantView::update()
{
    mModel->update();
}
