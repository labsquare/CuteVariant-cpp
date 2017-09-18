#include "listfieldwidget.h"

ListFieldWidget::ListFieldWidget(QWidget *parent)
    :AbstractFieldWidget(parent)
{

    mView = new QListWidget;



    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mView);
    vLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout * buttonLayout = new QHBoxLayout;
    QPushButton * addButton = new QPushButton(QIcon::fromTheme("list-add"),"Add");
    QPushButton * remButton = new QPushButton(QIcon::fromTheme("list-remove"),"Remove");
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(remButton);
//    addButton->setFlat(true);
//    remButton->setFlat(true);
    buttonLayout->setContentsMargins(0,0,0,0);

    connect(addButton, &QPushButton::clicked, this, &ListFieldWidget::add);
    connect(remButton, &QPushButton::clicked, this, &ListFieldWidget::rem);

    vLayout->addLayout(buttonLayout);
    setLayout(vLayout);

}

QVariant ListFieldWidget::value() const
{
    QStringList list;
    for (int i = 0; i<mView->count(); ++i)
    {
        list.append(mView->item(i)->text());
    }

    return QString("(\"%1\")").arg(list.join(","));
}

void ListFieldWidget::setValue(const QVariant &value)
{
    QVariantList list = value.toList();
    mView->clear();
    for (QVariant s : list){
        QListWidgetItem * item = new QListWidgetItem(s.toString());
        item->setFlags (item->flags () | Qt::ItemIsEditable);
        mView->addItem(item);


    }


}

void ListFieldWidget::add()
{
    QListWidgetItem * item = new QListWidgetItem("<edit>");
    item->setFlags (item->flags () | Qt::ItemIsEditable);

    mView->addItem(item);

    mView->setCurrentItem(item);
    mView->editItem(item);
}

void ListFieldWidget::rem()
{
    delete mView->takeItem(mView->currentRow());
}
