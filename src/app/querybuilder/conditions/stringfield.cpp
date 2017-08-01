#include "stringfield.h"

StringField::StringField(QWidget *parent)
    :AbstractField(parent)
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

QVariant StringField::value() const
{
    return mEdit->text();
}

void StringField::setValue(const QVariant &value)
{
    mEdit->setText(value.toString());
}

void StringField::setCompletion(QAbstractItemModel * m)
{
    mEdit->completer()->setModel(m);

}




