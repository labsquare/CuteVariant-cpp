#include "basedockwidget.h"
#include <QtWidgets>
BaseDockWidget::BaseDockWidget(QWidget *parent)
    :QDockWidget(parent)
{

    mToolBar     = new QToolBar;
    mTitleWidget = new QLabel();

    mToolBar->setIconSize(QSize(16,16));
    //  mToolBar->layout()->setContentsMargins(0,0,0,0);
    mToolBar->addWidget(mTitleWidget);

    // add spacer
    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mToolBar->addWidget(spacer);

    layout()->setContentsMargins(0,0,0,0);
    setTitleBarWidget(mToolBar);


}




void BaseDockWidget::setWidget(QWidget *w)
{
    QDockWidget::setWidget(w);
    //    w->setStyleSheet("{border:1px solid lightgray}");

}

void BaseDockWidget::setTitle(const QString &name)
{
    mTitleWidget->setText(name);
    setWindowTitle(name);
}

QString BaseDockWidget::title() const
{
    return mTitleWidget->text();
}

void BaseDockWidget::addAction(QAction *action)
{
    mToolBar->addAction(action);


}

QAction *BaseDockWidget::addAction(const QIcon &actionIcon, const QString &text, QObject *receiver, const char *member)
{

    QAction * ret = new QAction (actionIcon, text);
    connect(ret, SIGNAL(triggered(bool)), receiver, member);
    addAction(ret);
    return ret;

}

void BaseDockWidget::addToolWidget(QWidget *widget)
{

    mToolBar->addWidget(widget);
}


