#include "resultsview.h"

ResultsView::ResultsView(const QString &name, QWidget *parent)
    :QWidget(parent), mName(name)
{

    mView            = new QTreeView(this);
    mModel           = new ResultTreeModel(this);
    mTopToolBar      = new QToolBar;
    mBottomToolBar   = new QToolBar;
    mPageBox         = new QLineEdit;
    mPageValidator   = new QIntValidator;
    mCountLabel      = new QLabel;

    mNiceDelegate    = new ResultDelegate;
    mRawDelegate     = new QStyledItemDelegate;


    mView->header()->setStretchLastSection(false);
    mView->setModel(mModel);
    mView->setSortingEnabled(true);
    mView->setItemDelegate(mNiceDelegate);
    mView->setAlternatingRowColors(true);
    mView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // mView->setFrameStyle(QFrame::HLine);
    mView->setFrameShape(QFrame::NoFrame);
    QVBoxLayout * vLayout = new QVBoxLayout;


    mPageBox->setValidator(mPageValidator);
    mPageBox->setFrame(false);
    //mPageBox->setInputMask("9999999");
    mPageBox->setMaximumWidth(50);
    // mPageBox->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    mPageBox->setAlignment(Qt::AlignHCenter);


    mTopToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mTopToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    mTopToolBar->setStyleSheet("QToolBar{border-bottom: 1px solid lightgray}");
    mBottomToolBar->setStyleSheet("QToolBar{border-top: 1px solid lightgray}");


    vLayout->addWidget(mTopToolBar);
    vLayout->addWidget(mView);
    vLayout->addWidget(mBottomToolBar);
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);
    setLayout(vLayout);


    mTopToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mTopToolBar->addAction(FIcon(0xf193), "Save table", this, SLOT(save()));
    mTopToolBar->addAction(FIcon(0xf21d),"Export table", this, SLOT(exportCsv()));

    // setup delegate action
    mTopToolBar->addAction(FIcon(0xf3d8),"Layout", this, SLOT(changeDelegate()));


    mTopToolBar->layout()->setContentsMargins(0,0,0,0);

    mBottomToolBar->addAction(FIcon(0xf12c),"sql",this, SLOT(showSql()));
    mBottomToolBar->addWidget(mCountLabel);

    QWidget * spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mBottomToolBar->addWidget(spacer);

    mBottomToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    mBottomToolBar->setIconSize(QSize(20,20));
    mBottomToolBar->addAction(FIcon(0xf4ab),"<<", this, SLOT(pageFirst()));
    mBottomToolBar->addAction(FIcon(0xf4ae),"<", this, SLOT(pageDown()));
    mBottomToolBar->addWidget(mPageBox);
    mBottomToolBar->addAction(FIcon(0xf4ad),">", this, SLOT(pageUp()));
    mBottomToolBar->addAction(FIcon(0xf4ac),">>", this, SLOT(pageLast()));
    mBottomToolBar->layout()->setContentsMargins(0,0,0,0);




}

void ResultsView::setQuery(const cvar::VariantQuery &query)
{

    mQuery = query;
    cvar::VariantQuery temp = query;
    temp.setGroupBy({"chr","pos","ref","alt"});

    // 100 page constant for now
    int totalCount = cutevariant->variantsCount(temp);
    int pageCount  = totalCount / 100;
    mPageValidator->setRange(0, pageCount);

    mCountLabel->setText(QString("%1 variant(s) %2 page(s)").arg(totalCount).arg(pageCount));

    setFocus();

    mModel->setQuery(temp);
    setPage(0);


}


void ResultsView::pageUp()
{
    int page = mPageBox->text().toInt();
    if (page + 1 <= mPageValidator->top()){
        setPage(page+1);
    }
}

void ResultsView::pageDown()
{
    int page = mPageBox->text().toInt();
    if (page - 1 >= 0){
        setPage(page-1);
    }
}

void ResultsView::pageFirst()
{
    setPage(mPageValidator->bottom());
}

void ResultsView::pageLast()
{
    setPage(mPageValidator->top());
}

void ResultsView::setPage(int page)
{
    mPageBox->setText(QString::number(page));
    mPageBox->setAlignment(Qt::AlignHCenter);
    mModel->load(page*100, 100);

}

void ResultsView::save()
{
    if (mModel->isEmpty())
        return;

    QDialog dialog(this);
    QLineEdit * nameEdit = new QLineEdit(&dialog);
    QTextEdit * descEdit = new QTextEdit(&dialog);
    QDialogButtonBox * buttons = new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel, &dialog);
    QFormLayout * fLayout = new QFormLayout;

    fLayout->addRow("Table name", nameEdit);
    fLayout->addRow("Description", descEdit);
    fLayout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted,[&dialog](){dialog.accept();});
    connect(buttons, &QDialogButtonBox::rejected,[&dialog](){dialog.reject();});
    dialog.setLayout(fLayout);

    if (dialog.exec() == QDialog::Accepted)
    {

        cvar::View view;
//TODO
//        if (!cutevariant->addView(mModel->currentQuery(), nameEdit->text()))
//            QMessageBox::warning(this,"error", "cannot create table");

//        else
//            emit tableSaved();
    }



}

void ResultsView::exportCsv()
{

    if (mModel->isEmpty())
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",  tr("TSV (*.tsv)"));

    if (!fileName.isEmpty())
    {
        if (!mModel->exportCsv(fileName))
        {
            qDebug()<<Q_FUNC_INFO<<"cannot save file";
        }
    }
}

void ResultsView::showSql()
{
    QDialog infoBox;
    QPlainTextEdit * edit = new QPlainTextEdit(&infoBox);
    QVBoxLayout * infoLayout = new QVBoxLayout;
    infoLayout->addWidget(edit);
    edit->setPlainText(mModel->currentQuery().toSql());
    infoBox.setLayout(infoLayout);
    infoBox.setWindowTitle("raw sql");
    infoBox.exec();

}

void ResultsView::changeDelegate()
{

    if (mView->itemDelegate() == mNiceDelegate)
        mView->setItemDelegate(mRawDelegate);
    else
        mView->setItemDelegate(mNiceDelegate);

}

void ResultsView::contextMenuEvent(QContextMenuEvent *event)
{

    // strange.. I need to compute the map myself...
    QPoint p = mView->mapFromParent(event->pos()) - QPoint(0,mView->header()->height());
    QModelIndex index = mView->indexAt(p);

    if (index.isValid())
    {
        quint64 variantID = mModel->record(index).value("id").toInt();
        qDebug()<<variantID;
        cvar::Variant var = cutevariant->variant(variantID);


        QMenu menu(this);

        // HUGLY TODO !: Put all in model
        menu.addAction("add to favoris", [&var,this](){
           var.setFavoris(!var.isFavoris());
           qDebug()<<var.isFavoris();

           if (cutevariant->saveVariant(var))
               mModel->load();


        });

        menu.addAction(QIcon::fromTheme("edit-copy"), var.coordinate(),[&var](){
            qApp->clipboard()->setText(var.coordinate());
        });

        menu.addAction(QIcon::fromTheme("edit-copy"), var.name(),[&var](){
            qApp->clipboard()->setText(var.name());
        });

        menu.addSeparator();

        // show links

        for (cvar::VariantLink link : cutevariant->links())
        {
            QUrl varurl = link.toUrl(var);
            menu.addAction(link.icon(), link.name(),[varurl](){
                QDesktopServices::openUrl(varurl);

            });
        }

        menu.addSeparator();


        menu.addAction(QIcon::fromTheme("document-add"),"edit link ...",[&var](){

            LinkListDialog dialog;
            dialog.exec();

        });


        menu.exec(event->globalPos());

    }
}



QString ResultsView::name() const
{
    return mName;
}

void ResultsView::setName(const QString &name)
{
    mName = name;
}


