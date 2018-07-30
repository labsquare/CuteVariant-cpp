#ifndef BEDDOCKWIDGET_H
#define BEDDOCKWIDGET_H
#include <QtWidgets>
#include "basedockwidget.h"
#include "cutevariant.h"
class RegionDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    RegionDockWidget(QWidget * parent = nullptr);

    virtual void reset() override;

    QString region() const;

public Q_SLOTS:
    void addBedFile();


private:
    QTreeWidget * mView;

};

#endif // BEDDOCKWIDGET_H
