#include "conditionfieldfactory.h"

ConditionFieldFactory::ConditionFieldFactory()
{

}

AbstractFieldWidget *ConditionFieldFactory::widget(const cvar::Field &field)
{

    if (field.type() == cvar::Field::BOOL)
        return new BoolField;

    if (field.type() == cvar::Field::TEXT){
        StringFieldWidget * w = new StringFieldWidget;
//        QSqlQueryModel * model = new QSqlQueryModel(w);
//        model->setQuery(QString("SELECT DISTINCT(%1) FROM variants").arg(field.colname()));
//        w->setCompletion(model);
        return w;

    }

    if (field.type() == cvar::Field::INTEGER){
        IntegerFieldWidget *w = new IntegerFieldWidget;
//        QSqlQuery query(QString("SELECT MIN(%1) as min , MAX(%1) as max FROM variants").arg(field.colname()));
//        query.next();
//        w->setRange(query.record().value("min").toInt(),query.record().value("max").toInt() );
        return w;
    }

    if (field.type() == cvar::Field::REAL){
        DoubleFieldWidget *w = new DoubleFieldWidget;
//        QSqlQuery query(QString("SELECT MIN(%1) as min , MAX(%1) as max FROM variants").arg(field.colname()));
//        query.next();
//        w->setRange(query.record().value("min").toInt(),query.record().value("max").toInt() );
        return w;
    }

    return new StringFieldWidget;

}

QList<Operator::Type> ConditionFieldFactory::operatorsList(const cvar::Field &field)
{
    QList<Operator::Type> types;

    if (field.type() == cvar::Field::BOOL)
        types = {Operator::Equal};

    if (field.type() == cvar::Field::INTEGER || field.type() == cvar::Field::REAL)
        types = {
            Operator::Equal,
            Operator::NotEqual,
            Operator::MoreThan,
            Operator::MoreThanOrEqualTo,
            Operator::LessThan,
            Operator::LessThanOrEqualTo,
            Operator::Between
        };

    if (field.type() == cvar::Field::TEXT)
        types = {
            Operator::Equal,
            Operator::NotEqual,
            Operator::Like,
            Operator::In
        };


    return types;
}


