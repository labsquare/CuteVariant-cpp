#ifndef BASEDOCKWIDGET_H
#define BASEDOCKWIDGET_H
#include <QDockWidget>
#include <QLabel>

class BaseDockWidget : public QDockWidget
{
public:
    BaseDockWidget(QWidget * parent = 0);
    virtual void setWidget(QWidget * w);
    void setTitle(const QString& name);
    QString title() const;

private:
    QLabel * mTitleWidget;
};

#endif // BASEDOCKWIDGET_H
