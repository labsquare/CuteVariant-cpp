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

void VariantView::setCondition(const QString &condition)
{
    mModel->setCondition(condition);
}

void VariantView::update()
{
    mModel->update();
}
