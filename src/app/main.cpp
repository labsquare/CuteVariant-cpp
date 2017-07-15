#include <QApplication>
#include <QtCore>
#include "vcfvariantreader.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    VCFVariantReader reader("/tmp/exemples/test.chr22.ann.vcf");


    for (Field s : reader.fields())
    {
        qDebug()<<s.name()<<" "<<s.description();
    }


    return app.exec();
}
