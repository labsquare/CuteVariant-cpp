#ifndef RESULTDELEGATE_H
#define RESULTDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>

class ResultDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ResultDelegate(QObject * parent = nullptr);
   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


   QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


   const QHash<QString,QColor> impactColor {
       {"LOW", QColor("#71E096")},
       {"MODERATE", QColor("#F5A26F")},
       {"HIGH", QColor("#ed6d79")},
       {"MODIFIER", QColor("#55abe1")}
   };




};

#endif // RESULTDELEGATE_H
