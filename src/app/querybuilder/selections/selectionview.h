#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include "project.h"

class SelectionView : public QListView
{
    Q_OBJECT
public:
    explicit SelectionView(cvar::Project * prj, QWidget *parent = 0);
    QString tableName() const;


public Q_SLOTS:
    void load();

private:
    cvar::Project * mPrj;
    QStringListModel * mModel;
};

#endif // SELECTIONVIEW_H
