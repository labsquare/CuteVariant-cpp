#ifndef EDITLINKDIALOG_H
#define EDITLINKDIALOG_H
#include <QDialog>
#include <QtWidgets>
#include <QtCore>
#include "variantlink.h"
class EditLinkDialog : public QDialog
{
    Q_OBJECT
public:
    EditLinkDialog(QWidget * parent = nullptr);

    void setLink(const cvar::VariantLink& link);
    const cvar::VariantLink& link();


protected Q_SLOTS:
    void changeIcon();


private:
    QToolButton * miconButton;
    QLineEdit * mNameEdit;
    QLineEdit * mUrlEdit;
    cvar::VariantLink mCurrentLink;
};

#endif // EDITLINKDIALOG_H
