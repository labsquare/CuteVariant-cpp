#include "conditionfieldfactory.h"

ConditionFieldFactory::ConditionFieldFactory()
{

}

AbstractField *ConditionFieldFactory::widget(const cvar::Field &field)
{

    if (field.type() == cvar::Field::BOOL)
        return new BoolField;

    if (field.type() == cvar::Field::TEXT){
        StringField * w = new StringField;
        QSqlQueryModel * model = new QSqlQueryModel(w);
        model->setQuery(QString("SELECT DISTINCT(%1) FROM variants").arg(field.colname()));
        w->setCompletion(model);
        return w;

    }

    if (field.type() == cvar::Field::INTEGER){
        IntegerField *w = new IntegerField;
        QSqlQuery query(QString("SELECT MIN(%1) as min , MAX(%1) as max FROM variants").arg(field.colname()));
        query.next();
        w->setRange(query.record().value("min").toInt(),query.record().value("max").toInt() );
        return w;
    }

    if (field.type() == cvar::Field::REAL){
        DoubleField *w = new DoubleField;
        QSqlQuery query(QString("SELECT MIN(%1) as min , MAX(%1) as max FROM variants").arg(field.colname()));
        query.next();
        w->setRange(query.record().value("min").toInt(),query.record().value("max").toInt() );
        return w;
    }

    return new StringField;

}

QList<Operator> ConditionFieldFactory::operatorsList(const cvar::Field &field)
{







}


