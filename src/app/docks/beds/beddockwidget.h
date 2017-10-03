#ifndef BEDDOCKWIDGET_H
#define BEDDOCKWIDGET_H
#include <QtWidgets>
#include "basedockwidget.h"
#include "project.h"
class BedDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    BedDockWidget(QWidget * parent = nullptr);

    virtual void reset() override;

public Q_SLOTS:
    void addBedFile();


private:
    QTreeWidget * mView;

};

#endif // BEDDOCKWIDGET_H
