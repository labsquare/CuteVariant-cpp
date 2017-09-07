#include "selectionview.h"


SelectionView::SelectionView(QWidget *parent)
    :QListWidget(parent)
{
    setEditTriggers(NoEditTriggers);

//    viewport()->setAutoFillBackground( false );
//    setFrameShape(QFrame::NoFrame);

    setWindowTitle("Selection");
    // select first item
   // selectionModel()->select(mModel->index(0,0),QItemSelectionModel::Select);
}
//---------------------------------------------------------------------------------------------

QString SelectionView::tableName() const
{
    if (selectedItems().isEmpty())
        return "";

    return currentItem()->text();
}
//---------------------------------------------------------------------------------------------
void SelectionView::load()
{
    clear();
    for (cvar::VariantSelection selection : cutevariant->sqliteManager()->variantSelections())
    {
      QListWidgetItem * item  = new QListWidgetItem(selection.name());
      addItem(item);
    }

    setCurrentRow(0);

}
