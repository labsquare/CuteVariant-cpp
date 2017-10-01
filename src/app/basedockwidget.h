#ifndef BASEDOCKWIDGET_H
#define BASEDOCKWIDGET_H
#include <QtWidgets>
#include "qfonticon.h"
class BaseDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    BaseDockWidget(QWidget * parent = 0);
     void setTitle(const QString& name);
    QString title() const;

    void addAction(QAction * action);
    void addActionSpacer();

    QAction *addAction(const QIcon &actionIcon, const QString &text, QObject * receiver, const char *member);
    void addToolWidget(QWidget * widget);


    void setWidget(QWidget * w);

    virtual void reset(){}

    const QList<QAction *>& actions() const;

Q_SIGNALS:
    void changed();

private:
    QLabel * mTitleWidget;
    QToolBar * mToolBar;
    QList<QAction*> mActions;
};

#endif // BASEDOCKWIDGET_H
