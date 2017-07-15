#include <QApplication>
#include <QtCore>
#include "vcfvariantreader.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    VCFVariantReader reader("/tmp/exemples/test.chr22.ann.vcf");


    if (reader.device()->open(QIODevice::ReadOnly))
    {
        while (!reader.device()->atEnd())
        {
            Variant var = reader.readVariant();
            qDebug()<<var.chromosom()<<" "<<var.position()<<" "<<var.ref()<<" "<<var.alt();
        }
    }


    return app.exec();
}
