#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QtWidgets>
#include "qfonticon.h"
#include "selectionmodel.h"

class SelectionView : public QTreeView
{
    Q_OBJECT
public:
    explicit SelectionView( QWidget *parent = 0);
    QString tableName() const;
    void load();


private:

SelectionModel * mModel;



};

#endif // SELECTIONVIEW_H
