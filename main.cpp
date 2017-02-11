#include "mainwindow.h"
#include <QApplication>
#include "project.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Project prj("test.db");
//    prj.createSchema();

    QStringList list;
    list<<"/home/sacha/Bioinfo/tmp/pere.vcf";
//    list<<"/home/sacha/Bioinfo/tmp/mere.vcf";
//    list<<"/home/sacha/Bioinfo/tmp/fils.vcf";

   // list<<"/tmp/test.chr22.ann.vcf";

    prj.importVCF(list);



    return a.exec();
}
