#ifndef LINKDIALOG_H
#define LINKDIALOG_H
#include <QtWidgets>
#include "cutevariant.h"
#include "editlinkdialog.h"
#include "variantlink.h"

class LinkListDialog : public QDialog
{
    Q_OBJECT
public:
    LinkListDialog(QWidget * parent = nullptr);


public Q_SLOTS:
    void addLink();
    void remLink();
    void editLink();

protected:
    void load();

private:
    QTreeWidget * mView;
    QPushButton * mAddButton;
    QPushButton * mEditButton;
    QPushButton * mRemButton;
    QPushButton * mQuitButton;

    QList<cvar::VariantLink> mLinks;




};

#endif // LINKDIALOG_H
