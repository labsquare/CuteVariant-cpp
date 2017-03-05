#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H
#include <QtWidgets>
#include "LogicModel.h"
class ConditionWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ConditionWidget(QVariant::Type valueType = QVariant::String, QWidget *parent = 0);

     QString key();
     QString conditionOperator();
     QVariant value();
    void setValue(const QString& key, const QString& conditionOperator, const QVariant& value);

    void setFieldNames(const QStringList& fieldNames);

private:
    QComboBox * mKeyBox;
    QComboBox * mCompareOperatorBox;
    QWidget * mValueEdit;
    QItemEditorFactory *mFactory;
    QVariant::Type mType;

};

#endif // CONDITIONWIDGET_H
