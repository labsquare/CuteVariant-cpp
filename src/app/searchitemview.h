#ifndef SEARCHITEMVIEW_H
#define SEARCHITEMVIEW_H
#include <QtWidgets>
#include <QSortFilterProxyModel>

class SearchItemView : public QWidget
{
    Q_OBJECT
public:
    explicit SearchItemView(QAbstractItemView* baseview, QWidget *parent = nullptr);


    virtual void keyPressEvent(QKeyEvent * event);

private:
    QAbstractItemView * mBaseView;
    QToolBar * mBar;
    QLineEdit * mEdit;
    QSortFilterProxyModel * mProxyModel;
    QAbstractItemModel * mSourceModel;

};


#endif // SEARCHITEMVIEW_H
