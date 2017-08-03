#include "columnview.h"

ColumnView::ColumnView(QWidget *parent)
    :QTreeView(parent)
{
    mModel   = new ColumnModel();
    setModel(mModel);
    setWindowTitle(tr("Fields"));
    viewport()->setAutoFillBackground( false );
    setFrameShape(QFrame::NoFrame);
    header()->hide();

    load();
}

QStringList ColumnView::selectedColumns() const
{
    return mModel->selectedColumns();
}

void ColumnView::load()
{
    mModel->load();
}
