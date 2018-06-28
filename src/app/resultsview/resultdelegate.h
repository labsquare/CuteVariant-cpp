#ifndef RESULTDELEGATE_H
#define RESULTDELEGATE_H
#include <QItemDelegate>
#include <QPainter>
#include <QApplication>
#include "qfonticon.h"

class ResultDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ResultDelegate(QObject * parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:


    const QHash<QString,QColor> impactColor {
        {"LOW",     "#71E096"},
        {"MODERATE","#F5A26F"},
        {"HIGH",    "#ed6d79"},
        {"MODIFIER","#55abe1"}
    };


    // TODO  : more color IUPAC
    const QHash<QString,QColor> baseColor {
        {"A","#71E096"},
        {"C" ,"#668DE5"},
        {"G" ,"#000000"},
        {"T" ,"#ED6D79"}
    };

};

#endif // RESULTDELEGATE_H
