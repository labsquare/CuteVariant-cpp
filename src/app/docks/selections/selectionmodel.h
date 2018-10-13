#ifndef SELECTIONMODEL_H
#define SELECTIONMODEL_H
#include <QStandardItemModel>
#include "viewdatamapper.h"
#include "view.h"

class SelectionModel : public QStandardItemModel
{
public:
    SelectionModel(QObject * parent = nullptr);

    void load();



};

#endif // SELECTIONMODEL_H
