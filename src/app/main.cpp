#include <QApplication>
#include <QtCore>
#include "vcfvariantreader.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    VCFVariantReader reader("/tmp/exemples/freebayes.vcf");


    for (Sample s : reader.samples())
    {
        qDebug()<<s.name();
    }


    return app.exec();
}
