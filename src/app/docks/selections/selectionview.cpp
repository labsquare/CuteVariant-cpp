#include "selectionview.h"


SelectionView::SelectionView(QWidget *parent)
    :QTreeView(parent)
{

    mModel = new SelectionModel;
    setModel(mModel);
//    setEditTriggers(NoEditTriggers);
//    setColumnCount(2);

//    setIconSize(QSize(22,22));



//    header()->hide();

//    setSelectionBehavior(QAbstractItemView::SelectRows);
//    setSelectionMode(QAbstractItemView::SingleSelection);

//    setIndentation(0);

//    //    viewport()->setAutoFillBackground( false );
//    //    setFrameShape(QFrame::NoFrame);

//    setHeaderLabels({"name","count"});

//    setWindowTitle("Selection");
//    // select first item
    // selectionModel()->select(mModel->index(0,0),QItemSelectionModel::Select);
}
//---------------------------------------------------------------------------------------------

QString SelectionView::tableName() const
{
//    if (selectedItems().isEmpty())
//        return "";

//    return currentItem()->text(0);
}
//---------------------------------------------------------------------------------------------
void SelectionView::load()
{

    mModel->load();
//    clear();
//    // mandatory variant table name
//    QTreeWidgetItem * variantItem = new QTreeWidgetItem;
//    variantItem->setText(0,"variants");
//    variantItem->setText(1, "todo"); // TODO
//    variantItem->setIcon(0,FIcon(0xf24b));
//    variantItem->setTextAlignment(1,Qt::AlignRight);
//    addTopLevelItem(variantItem);

//    // mandatory Favoris table name
//    QTreeWidgetItem * favorisItem = new QTreeWidgetItem;
//    favorisItem->setText(0,"Favoris");
//    //favorisItem->setText(1, QString::number(cutevariant->variantsCount()));
//    favorisItem->setIcon(0,FIcon(0xf69c));
//    favorisItem->setTextAlignment(1,Qt::AlignRight);
//    addTopLevelItem(favorisItem);

//        for (cvar::View selection : cutevariant->views())
//        {
//            QTreeWidgetItem * item = new QTreeWidgetItem;
//            item->setText(0, selection.name());
//            item->setText(1,QString::number(selection.count()));
//            item->setToolTip(0, selection.description());
//            item->setTextAlignment(1,Qt::AlignRight);
//            item->setIcon(0,FIcon(0xf0ce));

//            addTopLevelItem(item);
//        }

//        header()->setSectionResizeMode(0,QHeaderView::Stretch);
//        header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);

//       setCurrentItem(variantItem);
}
//---------------------------------------------------------------------------------------------
