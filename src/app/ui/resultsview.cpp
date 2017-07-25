#include "resultsview.h"

ResultsView::ResultsView(core::Project *prj, QWidget *parent) : QWidget(parent)
{
    mPrj = prj;

    mView = new QTreeView;
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
    mPageBox->setInputMask("9999999");
    mPageBox->setMaximumWidth(50);

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


    mBottomToolBar->addAction(QIcon(),"<<", this, SLOT(pageFirst()));
    mBottomToolBar->addAction(QIcon(),"<", this, SLOT(pageDown()));
    mBottomToolBar->addWidget(mPageBox);
    mBottomToolBar->addAction(QIcon(),">", this, SLOT(pageUp()));
    mBottomToolBar->addAction(QIcon(),">>", this, SLOT(pageLast()));



}

void ResultsView::load()
{
    // 100 page constant for now
    int totalCount = mModel->totalVariantCount();

    mPageValidator->setRange(0, totalCount/100);

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
    load();

}
