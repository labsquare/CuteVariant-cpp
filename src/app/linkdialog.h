#ifndef LINKDIALOG_H
#define LINKDIALOG_H
#include <QtWidgets>

class LinkDialog : public QDialog
{
    Q_OBJECT
public:
    LinkDialog(QWidget * parent = nullptr);


public Q_SLOTS:
    void addLink();
    void remLink();

private:
    QListWidget * mView;
    QPushButton * mAddButton;
    QPushButton * mRemButton;
    QPushButton * mQuitButton;




};

#endif // LINKDIALOG_H
