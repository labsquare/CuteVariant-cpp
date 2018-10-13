//#include <QApplication>
#include <QtCore>
#include "qfonticon.h"
#include "mainwindow.h"

#include "variant.h"

#include "kcompressiondevice.h"

int main(int argc, char **argv)
{


    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");

    // https://cdn.materialdesignicons.com/2.3.54/
    QFontIcon::addFont(":/materialIcon");






 //   cutevariant->openDatabase("/tmp/test.db");



    //QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);


    //    cvar::GenericVCFReader reader("/home/sacha/Dev/CuteVariant/exemples/vcf/snpeff.example.vcf");

    //    for (auto& f : reader.fields())
    //        qDebug()<<f.name();

    //   reader.open();

    //    while (!reader.atEnd())
    //    {
    //        auto variant  = reader.readVariant();
    //        qDebug()<<variant.chromosom()<<" "<<variant.ref()<<" "<<variant.alt()<<" "<<variant.position()<<" "<<variant["hgvs_c"];

    //    }



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
