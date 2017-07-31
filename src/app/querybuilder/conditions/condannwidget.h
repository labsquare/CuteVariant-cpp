#ifndef CONDANNWIDGET_H
#define CONDANNWIDGET_H

#include <QtWidgets>

class CondAnnWidget: public QWidget
{
public:
    CondAnnWidget(QWidget * parent = nullptr);


private:
    QComboBox * mKeyBox;
    QComboBox * mOperatorBox;



};

#endif // CONDANNWIDGET_H
