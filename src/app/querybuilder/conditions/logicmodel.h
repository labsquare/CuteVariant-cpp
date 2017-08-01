#ifndef LOGICMODEL_H
#define LOGICMODEL_H
#include <QStandardItemModel>
#include <QInputDialog>


/*!
 * The following struct and class are used to manage the dynamic filter model
 */
class GroupItem;
class ConditionItem;
class LogicModel;




class GroupItem : public QStandardItem
{
public :
    GroupItem(const QString& logicOperator = QString());
    int type() const;

};

class ConditionItem :public  QStandardItem
{
public :
    enum ConditionRole {
        KeyRole = Qt::UserRole +1,
        OperatorRole,
        ValueRole
    };

    ConditionItem();
    ConditionItem(const QString& key, const QString& compareOperator, const QVariant& value);
    int type() const;
    void setValue(const QString& key, const QString& compareOperator, const QVariant& value);

    QString key() const;
    QString compareOperator() const;
    QVariant value() const;

};


class LogicModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum ItemType {
        LogicType     = QStandardItem::UserType +1,
        ConditionType = QStandardItem::UserType +2
    };

    LogicModel(QObject * parent = Q_NULLPTR);

    void createGroup(QStandardItem * parent = Q_NULLPTR);
    void createCondition(QStandardItem * parent);

//    static  QList<OperatorToRemove> conditionOperators() ;
//    static  QList<OperatorToRemove> logicOperators();

//    static OperatorToRemove conditionOperator(const QString& name) ;
//    static OperatorToRemove logicOperator(const QString& name);

    QString makeQuery() ;

    QString recursiveQuery(QStandardItem * item);


protected:


private:



};

#endif // LOGICMODEL_H
