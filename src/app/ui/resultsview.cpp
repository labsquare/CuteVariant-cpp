#include "resultsview.h"

ResultsView::ResultsView(core::Project *prj, QWidget *parent) : QWidget(parent)
{
    mPrj = prj;

    mView = new QTreeView(this);
    mModel = new ResultTreeModel(prj);
    mView->setModel(mModel);
    mView->setSortingEnabled(true);


    QVBoxLayout * vLayout = new QVBoxLayout;


    mTopToolBar    = new QToolBar;
    mBottomToolBar = new QToolBar;
    mPageBox       = new QLineEdit;
    mPageValidator = new QIntValidator;
    mCountLabel    = new QLabel;


    mPageBox->setValidator(mPageValidator);
    mPageBox->setFrame(false);
    //mPageBox->setInputMask("9999999");
    mPageBox->setMaximumWidth(50);
    mPageBox->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    mPageBox->setAlignment(Qt::AlignHCenter);
    connect(mPageBox,SIGNAL(returnPressed()),this,SLOT(setQuery()));
    mTopToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mTopToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mBottomToolBar->addWidget(mCountLabel);
    mBottomToolBar->addWidget(spacer);

    vLayout->addWidget(mTopToolBar);
    vLayout->addWidget(mView);
    vLayout->addWidget(mBottomToolBar);
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);
    setLayout(vLayout);



    mBottomToolBar->setIconSize(QSize(16,16));
    mBottomToolBar->addAction(QIcon::fromTheme("arrow-left-double"),"<<", this, SLOT(pageFirst()));
    mBottomToolBar->addAction(QIcon::fromTheme("arrow-left"),"<", this, SLOT(pageDown()));
    mBottomToolBar->addWidget(mPageBox);
    mBottomToolBar->addAction(QIcon::fromTheme("arrow-right"),">", this, SLOT(pageUp()));
    mBottomToolBar->addAction(QIcon::fromTheme("arrow-right-double"),">>", this, SLOT(pageLast()));



}

void ResultsView::setQuery(const core::VariantQuery &query)
{

    core::VariantQuery temp = query;
    temp.setGroupBy({"chr","pos","ref","alt"});

    // 100 page constant for now
    int totalCount = mPrj->sqliteManager()->variantsCount(temp);
    mPageValidator->setRange(0, totalCount/100);

    mCountLabel->setText(QString("%1 r(s)").arg(totalCount));

    setFocus();
    setupToolbar();

    mModel->setQuery(temp);
    setPage(0);


}

void ResultsView::pageUp()
{
    int page = mPageBox->text().toInt();
    if (page + 1 <= mPageValidator->top()){
        setPage(page+1);
    }
}

void ResultsView::pageDown()
{
    int page = mPageBox->text().toInt();
    if (page - 1 >= 0){
        setPage(page-1);
    }
}

void ResultsView::pageFirst()
{
    setPage(mPageValidator->bottom());
}

void ResultsView::pageLast()
{
    setPage(mPageValidator->top());
}

void ResultsView::setPage(int page)
{
    mPageBox->setText(QString::number(page));
    mPageBox->setAlignment(Qt::AlignHCenter);
    mModel->load(page*100, 100);

}

void ResultsView::contextMenuEvent(QContextMenuEvent *event)
{

    // strange.. I need to compute the map myself...
    QPoint p = mView->mapFromParent(event->pos()) - QPoint(0,mView->header()->height());
    QModelIndex index = mView->indexAt(p);

    if (index.isValid())
    {

        qDebug()<<mModel->record(index).value("id");
        //        int variantID = mModel->item(index.row())->data().toInt();
        //        qDebug()<<variantID;
        //        core::Variant var = mPrj->sqliteManager()->variant(variantID);

        //        QMenu menu(this);
        //        menu.addAction(QIcon::fromTheme("edit-copy"), var.coordinate(),[&var](){
        //            qApp->clipboard()->setText(var.coordinate());
        //        });

        //        menu.addAction(QIcon::fromTheme("edit-copy"), var.name(),[&var](){
        //            qApp->clipboard()->setText(var.name());
        //        });

        //        menu.addAction(QIcon::fromTheme("edit-link"), "IGV",[&var](){
        //            QDesktopServices::openUrl(var.igvUrl());
        //        });

        //        menu.addAction(QIcon::fromTheme("edit-link"), "Varsome",[&var](){
        //            QDesktopServices::openUrl(var.varsomeUrl());
        //        });

        //        menu.exec(event->globalPos());

    }
}

void ResultsView::setupToolbar()
{
    mTopToolBar->clear();
    QComboBox * orderMenu = new QComboBox();
    for (int i=0 ; i<mModel->columnCount(); ++i)
    {
        orderMenu->addItem(mModel->headerData(i,Qt::Horizontal, Qt::DisplayRole).toString());
    }

    mTopToolBar->addWidget(orderMenu);

}
