#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QtWidgets>
#include <QStandardItemModel>
#include "project.h"

class SelectionView : public QListView
{
    Q_OBJECT
public:
    explicit SelectionView( QWidget *parent = 0);
    QString tableName() const;


public Q_SLOTS:
    void load();

private:
    QStringListModel * mModel;
};

#endif // SELECTIONVIEW_H
