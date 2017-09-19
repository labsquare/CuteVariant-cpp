#ifndef METADATADOCKWIDGET_H
#define METADATADOCKWIDGET_H
#include "basedockwidget.h"
#include <QtWidgets>
#include "project.h"

class MetadataDockWidget : public BaseDockWidget
{
public:
    MetadataDockWidget(QWidget * parent = nullptr);

    virtual void reset() override;


private:
    QTreeWidget * mView;


};

#endif // METADATADOCKWIDGET_H
