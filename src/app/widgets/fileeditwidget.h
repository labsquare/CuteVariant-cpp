#ifndef FILEEDITWIDGET_H
#define FILEEDITWIDGET_H

#include <QtWidgets>

class FileEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileEditWidget(QWidget *parent = nullptr);

    QString text() const;


    QLineEdit *edit() const;

public Q_SLOTS:
    void browse();


private:
    QLineEdit * mEdit;
    QPushButton * mButton;

};

#endif // FILEEDITWIDGET_H
