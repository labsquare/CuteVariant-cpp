#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include "project.h"
#include "variantmodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Project * prj = new Project("/home/sacha/Dev/CuteVariant/variant.db");

    VariantModel * model = new VariantModel(prj);

    QStringList ann;
    ann<<"ANN_1"<<"ANN_2";
    model->setAnnotationColumns(ann);

    QTableView view;
    view.setModel(model);

    model->update();

    view.show();




    return a.exec();
}
