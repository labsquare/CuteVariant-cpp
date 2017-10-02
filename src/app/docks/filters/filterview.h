#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "filtermodel.h"
#include "project.h"
#include "filterdelegate.h"
#include "filterdialog.h"

class FilterView : public QTreeWidget
{
    Q_OBJECT
public:
    FilterView(QWidget * parent = 0);
    enum ItemType {
        LogicType,
        ConditionType
    };
    QString query();

public Q_SLOTS:
    void addLogic(LogicItem * item);
    void addCondition(ConditionItem * item);
    void editCondition(const QModelIndex& index);
    void removeSelections();

private:
    QString recursiveQuery(QTreeWidgetItem * item);


protected Q_SLOTS:
    void updateActionAvaible();


Q_SIGNALS:
    void changed();


private:
    FilterDelegate * mDelegate;





};

#endif // LOGICVIEW_H
