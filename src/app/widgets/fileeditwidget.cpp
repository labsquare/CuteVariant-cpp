#include "fileeditwidget.h"

FileEditWidget::FileEditWidget(QWidget *parent) : QWidget(parent)
{
    mEdit = new QLineEdit();
    mButton = new QPushButton(tr("Browse ..."));

    QHBoxLayout * hlayout = new QHBoxLayout;
    hlayout->addWidget(mEdit);
    hlayout->addWidget(mButton);

    setLayout(hlayout);

    connect(mButton, &QPushButton::clicked, this, &FileEditWidget::browse);

    hlayout->setContentsMargins(0,0,0,0);

}

 QString FileEditWidget::text() const
{
    return mEdit->text();
}

void FileEditWidget::browse()
{

    QString filename = QFileDialog::getOpenFileName(this,"select a file",  QDir::homePath());

    if (filename.isEmpty())
        return ;

    mEdit->setText(filename);





}

QLineEdit *FileEditWidget::edit() const
{
    return mEdit;
}
