#include "resultdelegate.h"





ResultDelegate::ResultDelegate(QObject *parent)
    :QItemDelegate(parent)
{

    setObjectName("snpEff");

}

void ResultDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QPalette pal    = qApp->palette("QTreeView");
    QString colname = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    bool select     = option.state & QStyle::State_Selected ;

    painter->save();

    QItemDelegate::drawBackground(painter,option,index);


    // Draw selection
//    if (select) {
//        QRect selectedRect = option.rect;
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(pal.brush(QPalette::Highlight));
//        painter->drawRect(selectedRect);
//    }

//    else
//    {
//        QRect selectedRect = option.rect;
//        painter->setPen(Qt::NoPen);
//        painter->setBrush(index.row() % 2 ? pal.color(QPalette::Base):  pal.color(QPalette::AlternateBase));
//        painter->drawRect(selectedRect);

//    }

    if (colname.toLower() == "ref" || colname.toLower() == "alt")
    {
        QString value = index.data().toString();
        int x = option.rect.x();
        int y = option.rect.center().y();
        QFontMetrics metrics(painter->font());


        for (const QChar& c : value)
        {
            painter->setPen(QPen(baseColor.value(c, Qt::lightGray)));
            painter->drawText(x,y, c);

            x+= metrics.width(c);
        }

        painter->restore();
        return;
    }


    if (colname.toLower() == "ann_impact")
    {

        QColor col = impactColor.value(index.data().toString(), pal.color(QPalette::Text));
        painter->setPen(QPen(select ? pal.color(QPalette::HighlightedText) : col));
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
        painter->restore();
        return;

    }

    if (colname.toLower() == "ann_impact_so")
    {
        QStringList soTerms = index.data().toString().split("&");
        QRect rect;
        QFont font = painter->font();
        font.setPixelSize(10);
        painter->setFont(font);
        QFontMetrics metrics(painter->font());
        rect.setX(option.rect.x());
        rect.setY(option.rect.center().y() - 5);


        for (QString& so : soTerms )
        {

            QColor bgColor = "#808080";

            // TODO : more exaustif
            if (so.toLower().contains("stop"))
                bgColor = "#808080";
            if (so.toLower().contains("utr"))
                bgColor = "#911eb4";
            if (so.toLower().contains("splice"))
                bgColor = "#f58231";
            if (so.toLower().contains("intron"))
                bgColor = "#0082c8";
            if (so.toLower().contains("intergenic"))
                bgColor = "#3cb44b";
            if (so.toLower().contains("frameshift"))
                bgColor = "#e6194b";
            if (so.toLower().contains("missense"))
                bgColor = "#f032e6";

            painter->setBrush(bgColor);


            so = so.simplified();
            rect.setWidth(metrics.width(so) + 4);
            rect.setHeight(metrics.height() + 4);


            painter->setPen(Qt::NoPen);
            painter->drawRoundedRect(rect,3,3);
            painter->setPen(Qt::white);
            painter->drawText(rect, Qt::AlignCenter, so);

            rect.translate(rect.width()+4,0);

        }
        painter->restore();

        return;
    }

    if (colname.toLower() == "ann_gene")
    {

        QColor col = QColor("#55abe1");
        painter->setPen(QPen(select ? pal.color(QPalette::HighlightedText) : col));
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
        painter->restore();
        return;

    }


    if (colname.toLower().contains(QRegularExpression("gt$")))
    {
    // TODO regexp
        QString gt = index.data().toString();
        QIcon icon = QIcon(":/gt_unknown");

        if (gt == "1/1" || gt == "1|1")
            icon = QIcon(":/gt_mut");

        if (gt == "1/0" || gt == "0/1" || gt == "1|0" || gt == "0|1")
            icon = QIcon(":/gt_hetero");

          if (gt == "0/0" || gt == "0|0")
            icon = QIcon(":/gt_wt");

        painter->drawPixmap(option.rect.center().x(), option.rect.center().y() - 8 ,icon.pixmap(16,16));

        painter->restore();
        return;

    }


    painter->setPen(QPen(pal.color(select ? QPalette::HighlightedText : QPalette::Text)));
    painter->drawText(option.rect, Qt::AlignLeft|Qt::AlignVCenter, index.data().toString());





    //    if (colname.toLower() == "ann_impact")
    //    {
    //        painter->setPen(QPen(Qt::red));
    //        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
    //    }


    //    else
    // QStyledItemDelegate::paint(painter, option, index);


}

QSize ResultDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    return QSize(0,30);


}
