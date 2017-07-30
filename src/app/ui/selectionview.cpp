#include "selectionview.h"


SelectionView::SelectionView(core::Project *prj, QWidget *parent)
    :QListView(parent), mPrj(prj)
{
    mModel = new QStringListModel;
    setModel(mModel);

    viewport()->setAutoFillBackground( false );
    setFrameShape(QFrame::NoFrame);

    setWindowTitle("Selection");
}

QString SelectionView::tableName() const
{
    return mModel->data(currentIndex(), Qt::DisplayRole).toString();
}

void SelectionView::load()
{

    QStringList list;
    for (core::VariantSelection selection : mPrj->sqliteManager()->variantSelections())
        list.append(selection.name());

    mModel->setStringList(list);


}
