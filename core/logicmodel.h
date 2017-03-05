#ifndef LOGICMODEL_H
#define LOGICMODEL_H
#include <QStandardItemModel>
#include <QInputDialog>


struct Operator;
class GroupItem;
class ConditionItem;
class LogicModel;


struct Operator{
    QString name;
    QString symbol;
    QString description;
};


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

    static  QList<Operator> conditionOperators() ;
    static  QList<Operator> logicOperators();

    static Operator conditionOperator(const QString& name) ;
    static Operator logicOperator(const QString& name);

    QString makeQuery() ;

    QString recursiveQuery(QStandardItem * item);


protected:


private:

    static QHash<QString,Operator> sLogicOperator;
    static QHash<QString,Operator> sConditionOperator;


};

#endif // LOGICMODEL_H
