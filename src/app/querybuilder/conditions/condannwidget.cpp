#include "condannwidget.h"

CondAnnWidget::CondAnnWidget(QWidget * parent)
    :QWidget(parent)
{

    QFormLayout * vLayout = new QFormLayout;
    mKeyBox = new QComboBox;
    mOperatorBox = new QComboBox;

    vLayout->addRow("Columns",mKeyBox);
    vLayout->addRow("Operator",mOperatorBox);


    vLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    setLayout(vLayout);

    setWindowTitle("Columns");


}
