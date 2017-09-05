#include "basedockwidget.h"
#include <QtWidgets>
BaseDockWidget::BaseDockWidget(QWidget *parent)
    :QDockWidget(parent)
{

    auto t = new QToolBar;
    t->setIconSize(QSize(16,16));

    t->layout()->setContentsMargins(0,0,0,0);

    mTitleWidget = new QLabel();
    t->addWidget(mTitleWidget);

    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    t->addWidget(spacer);
    t->addAction(QIcon::fromTheme("document-save"),"save");
    t->addAction(QIcon::fromTheme("document-save"),"save");
    t->addAction(QIcon::fromTheme("document-save"),"save");

    layout()->setContentsMargins(0,0,0,0);
    setTitleBarWidget(t);


}

void BaseDockWidget::setWidget(QWidget *w)
{

    QDockWidget::setWidget(w);


}

void BaseDockWidget::setTitle(const QString &name)
{
    mTitleWidget->setText(name);
}

QString BaseDockWidget::title() const
{
    return mTitleWidget->text();
}
