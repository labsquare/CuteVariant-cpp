#ifndef BASEDOCKWIDGET_H
#define BASEDOCKWIDGET_H
#include <QtWidgets>

class BaseDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    BaseDockWidget(QWidget * parent = 0);
     void setTitle(const QString& name);
    QString title() const;

    void addAction(QAction * action);
    void setWidget(QWidget * w);

    virtual void reset(){}

Q_SIGNALS:
    void changed();

private:
    QLabel * mTitleWidget;
    QToolBar * mToolBar;
    QList<QAction*> mActions;
};

#endif // BASEDOCKWIDGET_H
