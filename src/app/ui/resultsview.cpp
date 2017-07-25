#include "resultsview.h"

ResultsView::ResultsView(core::Project *prj, QWidget *parent) : QWidget(parent)
{
    mPrj = prj;

    mView = new QTreeView(this);
    mModel = new ResultsModel(prj);
    mView->setModel(mModel);


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
    connect(mPageBox,SIGNAL(returnPressed()),this,SLOT(load()));
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

    mTopToolBar->addAction("Sort");
    mTopToolBar->addAction("Group By");
    mTopToolBar->addAction("Export");


    mBottomToolBar->setIconSize(QSize(16,16));
    mBottomToolBar->addAction(QFontIcon::icon(0xf100),"<<", this, SLOT(pageFirst()));
    mBottomToolBar->addAction(QFontIcon::icon(0xf104),"<", this, SLOT(pageDown()));
    mBottomToolBar->addWidget(mPageBox);
    mBottomToolBar->addAction(QFontIcon::icon(0xf105),">", this, SLOT(pageUp()));
    mBottomToolBar->addAction(QFontIcon::icon(0xf101),">>", this, SLOT(pageLast()));



}

void ResultsView::load()
{
    setFocus();
    // 100 page constant for now
    int totalCount = mModel->totalVariantCount();

    mPageValidator->setRange(0, totalCount/100);

    if (mPageBox->text().isEmpty())
        mPageBox->setText("0");

    mModel->load(mPageBox->text().toInt() * 100, 100 );
    mCountLabel->setText(QString("%1 variant(s)").arg(mModel->totalVariantCount()));

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
    load();

}

void ResultsView::contextMenuEvent(QContextMenuEvent *event)
{

    // strange.. I need to compute the map myself...
    QPoint p = mView->mapFromParent(event->pos()) - QPoint(0,mView->header()->height());
    QModelIndex index = mView->indexAt(p);

    if (index.isValid())
    {
        int variantID = mModel->item(index.row())->data().toInt();
        core::Variant var = mPrj->sqliteManager()->variant(variantID);

        QMenu menu(this);
        menu.addAction(QFontIcon::icon(0xf0ea), var.coordinate(),[&var](){
           qApp->clipboard()->setText(var.coordinate());
        });

        menu.addAction(QFontIcon::icon(0xf0ea), var.name(),[&var](){
            qApp->clipboard()->setText(var.name());
        });

        menu.addAction(QFontIcon::icon(0xf08e), "IGV",[&var](){
            QDesktopServices::openUrl(var.igvUrl());
        });

        menu.addAction(QFontIcon::icon(0xf08e), "Varsome",[&var](){
            QDesktopServices::openUrl(var.varsomeUrl());
        });

        menu.exec(event->globalPos());



    }

}
