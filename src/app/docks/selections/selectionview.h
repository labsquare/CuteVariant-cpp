#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QtWidgets>
#include "qfonticon.h"
#include "cutevariant.h"
#include "qfonticon.h"
class SelectionView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SelectionView( QWidget *parent = 0);
    QString tableName() const;
    void load();

public Q_SLOTS:
    void removeSelection();



};

#endif // SELECTIONVIEW_H
