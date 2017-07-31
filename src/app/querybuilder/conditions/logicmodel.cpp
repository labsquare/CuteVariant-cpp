#include "logicmodel.h"
#include <QDebug>

QHash<QString,Operator> LogicModel::sLogicOperator ={
    {"and",{"and", "&&", QObject::tr("all is true")}},
    {"or" ,{"or", "||",  QObject::tr("one must be true")}}
};


QHash<QString,Operator> LogicModel::sConditionOperator ={
    {"gt",{"gt", ">", QObject::tr("greater than")}},
    {"gte",{"gte", ">=", QObject::tr("greater than or equal")}},
    {"lt",{"lt", "<", QObject::tr("lesser than")}},
    {"lte",{"lte", "<=", QObject::tr("lesser than or equal")}},
    {"eq",{"eq", "=", QObject::tr("equal")}},
    {"neq",{"neq", "=", QObject::tr("not equal")}}
};



GroupItem::GroupItem(const QString &logicOperator)
{
    setText(logicOperator);
    QFont f = font();
    f.setBold(true);
    setFont(f);
    setCheckable(true);

    setDropEnabled(true);

   // setIcon(QFontIcon::icon(0xf1b3));

}

int GroupItem::type() const
{
    return LogicModel::LogicType;
}



//============================================

ConditionItem::ConditionItem()
    :QStandardItem()
{
    setDropEnabled(false);

}

ConditionItem::ConditionItem(const QString &key, const QString &compareOperator, const QVariant &value)
{
    setValue(key, compareOperator,value);
    setDropEnabled(false);
}

int ConditionItem::type() const
{
    return LogicModel::ConditionType;
}

void ConditionItem::setValue(const QString &key, const QString &compareOperator, const QVariant &value)
{
    setData(key, KeyRole);
    setData(compareOperator, OperatorRole);
    setData(value, ValueRole);
    setText(QString("%1 %2 %3").arg(key).arg(compareOperator).arg(value.toString()));
   // setIcon(QFontIcon::icon(0xf1b2));
}

QString ConditionItem::key() const
{
    return data(KeyRole).toString();
}

QString ConditionItem::compareOperator() const
{
    return data(OperatorRole).toString();
}

QVariant ConditionItem::value() const
{
    return data(ValueRole);
}


//============================================
LogicModel::LogicModel(QObject * parent)
    :QStandardItemModel(parent)
{

    createGroup();
  //  createCondition(item(0,0));



}

void LogicModel::createGroup(QStandardItem *parent)
{

    Operator op = LogicModel::logicOperator("and");
    GroupItem * gp = new GroupItem(op.name.toUpper());
    gp->setToolTip(op.description);

    if (parent == Q_NULLPTR)
        appendRow(gp);
    else
        parent->appendRow(gp);

}

void LogicModel::createCondition(QStandardItem *parent)
{
    ConditionItem * item = new ConditionItem;
    item->setValue("chr", "==", "'chr3'");
    parent->appendRow(item);
}

QList<Operator> LogicModel::logicOperators()
{
    return sLogicOperator.values();
}

QList<Operator> LogicModel::conditionOperators()
{
    return sConditionOperator.values();
}

Operator LogicModel::conditionOperator(const QString &name)
{
    return sConditionOperator.value(name);
}

Operator LogicModel::logicOperator(const QString &name)
{
    return sLogicOperator.value(name);
}

QString LogicModel::makeQuery()
{

    QString out = recursiveQuery(item(0,0));

    if (out == "(AND)")
        return QString();

    return out;


}

QString LogicModel::recursiveQuery(QStandardItem *item)
{

    if (item->rowCount() == 0)
        return "("+item->text()+")";

    QStringList list;
    for (int i = 0; i< item->rowCount(); ++i)
    {
        list.append(" "+recursiveQuery(item->child(i))+" ");

    }

    qDebug()<<list;

    QString out ;

        if (item->text() =="AND")
            out = list.join("AND");

        if (item->text() =="OR")
            out = list.join("OR");



    return "("+out+")";


}




