#include "columnview.h"

ColumnView::ColumnView(cvar::Project *prj, QWidget *parent)
    :QTreeView(parent)
{
    mProject = prj;
    mModel   = new ColumnModel(prj);
    setModel(mModel);
    setWindowTitle(tr("Fields"));
    viewport()->setAutoFillBackground( false );
    setFrameShape(QFrame::NoFrame);
    header()->hide();
}

QStringList ColumnView::selectedColumns() const
{
    return mModel->selectedColumns();
}

void ColumnView::load()
{
    mModel->load();
}
