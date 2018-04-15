//#include <QApplication>
#include <QtCore>

#include "project.h"
#include "genotype.h"
#include "filterdialog.h"
#include "qfonticon.h"
#include "mainwindow.h"
#include "snpeffvcfteader.h"



using namespace cvar;

int main(int argc, char **argv)
{


    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");

    QFontIcon::addFont(":/materialIcon");

    //    Project prj("/tmp/variant.db");
    //    prj.importFile("/tmp/TRIO1.family.vcf");


    //    for (Field f : reader->parseHeader("INFO"))
    //    {
    //        qDebug()<<f.colname();
    //    }


        MainWindow win;
        win.show();

      //  win.hide();


//    VariantQuery query = VariantQuery::fromVql(R"(SELECT chr,pos,genotype("saca").gt, genotype("boby").gt FROM variants)");


//    qDebug()<<query;
//    qDebug()<<query.sqlColumns();



//    SnpEffVCFReader reader("/home/sacha/test.vcf");


//    for (auto i : reader.fields())
//        qDebug()<<i.name();

//    qDebug()<<"===";

////    for (auto i : reader.metadatas().keys())
////        qDebug()<<i<<" "<<reader.metadatas()[i];

//    if (reader.open())
//    {
//        while (!reader.atEnd())
//        {
//            qDebug()<<reader.readVariant().annotation("ANN_GENE");

//        }

//    }



    app.exec();





}
