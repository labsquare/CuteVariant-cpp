#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QtWidgets>
#include <QStandardItemModel>
#include "project.h"

class SelectionView : public QListWidget
{
    Q_OBJECT
public:
    explicit SelectionView( QWidget *parent = 0);
    QString tableName() const;


    void load();


};

#endif // SELECTIONVIEW_H
