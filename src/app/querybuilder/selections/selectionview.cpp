#include "selectionview.h"


SelectionView::SelectionView(QWidget *parent)
    :QListView(parent)
{
    mModel = new QStringListModel;
    setModel(mModel);

    viewport()->setAutoFillBackground( false );
    setFrameShape(QFrame::NoFrame);

    setWindowTitle("Selection");

    load();
}

QString SelectionView::tableName() const
{
    return mModel->data(currentIndex(), Qt::DisplayRole).toString();
}

void SelectionView::load()
{

    QStringList list;
    for (cvar::VariantSelection selection : cutevariant->sqliteManager()->variantSelections())
        list.append(selection.name());

    mModel->setStringList(list);


}
