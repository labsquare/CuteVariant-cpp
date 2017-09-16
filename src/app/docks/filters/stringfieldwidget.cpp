#include "stringfieldwidget.h"

StringFieldWidget::StringFieldWidget(QWidget *parent)
    :AbstractFieldWidget(parent)
{

    mEdit = new QLineEdit(this);
    mCompleter = new QCompleter(this);
    mEdit->setCompleter(mCompleter);

    mCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    mCompleter->setCompletionColumn(0);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addWidget(mEdit);
    setLayout(vLayout);
}

QVariant StringFieldWidget::value() const
{
    return mEdit->text();
}

void StringFieldWidget::setValue(const QVariant &value)
{
    mEdit->setText(value.toString());
}

void StringFieldWidget::setCompletion(QAbstractItemModel * m)
{
    mEdit->completer()->setModel(m);

}




