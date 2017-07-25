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
    mPageBox       = new QSpinBox;
    mCountLabel    = new QLabel;

    mPageBox->setFrame(false);

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


    mBottomToolBar->addAction("<<");
    mBottomToolBar->addAction("<");
    mBottomToolBar->addWidget(mPageBox);
    mBottomToolBar->addAction(">");
    mBottomToolBar->addAction(">>");



}

void ResultsView::load()
{
    mModel->load();
    mCountLabel->setText(QString("%1 variant(s)").arg(mModel->variantCount()));
}
