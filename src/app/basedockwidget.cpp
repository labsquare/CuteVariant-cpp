#include "basedockwidget.h"
#include <QtWidgets>
BaseDockWidget::BaseDockWidget(QWidget *parent)
    :QDockWidget(parent)
{

    mToolBar     = new QToolBar;
    mTitleWidget = new QLabel();

    QLabel * grapLabel =  new QLabel;
    grapLabel->setPixmap(FIcon(0xf047).pixmap(16));

    mToolBar->setIconSize(QSize(20,20));
    //  mToolBar->layout()->setContentsMargins(0,0,0,0);

   // mToolBar->addWidget(grapLabel);
   // mToolBar->addWidget(mTitleWidget);

    // add spacer
//    QWidget * spacer = new QWidget();
//    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    mToolBar->addWidget(spacer);

    layout()->setContentsMargins(0,0,0,0);
    //setTitleBarWidget(mToolBar);

   // setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);


}




void BaseDockWidget::setWidget(QWidget *w)
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mToolBar);
    vLayout->addWidget(w);

    vLayout->setSpacing(1);
    vLayout->setContentsMargins(0,0,0,0);

    QWidget * ww = new QWidget;
    ww->setLayout(vLayout);

    QDockWidget::setWidget(ww);

}

const QList<QAction *> &BaseDockWidget::actions() const
{
    return mActions;
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
    mActions.append(action);
}

void BaseDockWidget::addActionSpacer()
{
    QWidget * spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mToolBar->addWidget(spacer);
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


