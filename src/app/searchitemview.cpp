#include "searchitemview.h"

SearchItemView::SearchItemView(QAbstractItemView *baseview, QWidget *parent)
    :QWidget(parent), mBaseView(baseview)
{

    mSourceModel = baseview->model();
    mProxyModel  = new QSortFilterProxyModel();
    mProxyModel->setSourceModel(mSourceModel);

    baseview->setModel(mProxyModel);

    mBar = new QToolBar;
    mEdit = new QLineEdit;

    mBar->addWidget(mEdit);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mBaseView);
    //mainLayout->addWidget(mBar);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(1);
    mBar->layout()->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);

    connect(mEdit, SIGNAL(textEdited(QString)), mProxyModel, SLOT(setFilterFixedString(QString)));

}

void SearchItemView::keyPressEvent(QKeyEvent *event)
{

    if (event->matches(QKeySequence::Find))
    {
        if (mBar->isVisible())
            mBar->hide();
        else
            mBar->show();

    }

    return QWidget::keyPressEvent(event);


}
