#include "columnview.h"

ColumnView::ColumnView(QWidget *parent)
    :QTreeView(parent)
{
    mModel   = new ColumnModel();
    setModel(mModel);
    setWindowTitle(tr("Fields"));
    viewport()->setAutoFillBackground( false );
   // setFrameShape(QFrame::NoFrame);
    header()->hide();

//    setStyleSheet(
//        "QTreeView::indicator:unchecked {image: url(:/uncheck.png);}"
//        "QTreeView::indicator:checked {image: url(:/check.png);}"
//      );

    setAlternatingRowColors(true);


}

QStringList ColumnView::selectedColumns() const
{
    return mModel->selectedColumns();
}

void ColumnView::load()
{
    mModel->load();
}

void ColumnView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QModelIndex index = indexAt(event->pos());
    cvar::Field field = mModel->field(index);

    if (!field.isNull())
    {
        qDebug()<<"hello";

        menu.addAction("show Description", [field](){

        QMessageBox::information(nullptr,field.name(), field.description());

        });


        menu.addAction("add Filter ...", [field,this](){

              FilterDialog dialog;
              dialog.setField(field);
              if (dialog.exec())
              {
                  emit filterItemCreated(dialog.createCondition());
              }


        });

        menu.exec(event->globalPos());




    }




}



