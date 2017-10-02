#ifndef LOGICMODEL_H
#define LOGICMODEL_H
#include <QStandardItemModel>
#include <QInputDialog>
#include "filteritem.h"
#include "logicitem.h"

class ConditionItem;
class LogicItem;
class FilterModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum Type{
        LogicType,
        ConditionalType
    };

    FilterModel(QObject * parent = Q_NULLPTR);

    void addLogic(LogicItem * item , QStandardItem * parent = nullptr);
    void addCondition(ConditionItem * item , QStandardItem * parent);

//    static  QList<OperatorToRemove> conditionOperators() ;
//    static  QList<OperatorToRemove> logicOperators();

//    static OperatorToRemove conditionOperator(const QString& name) ;
//    static OperatorToRemove logicOperator(const QString& name);

    QString makeQuery() ;

    QString recursiveQuery(QStandardItem * item);


    QVariant data(const QModelIndex &index, int role) const override;
protected:


private:



};

#endif // LOGICMODEL_H
