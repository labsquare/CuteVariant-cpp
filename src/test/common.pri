 
QT += concurrent sql

LIBS += -L$$PWD/../bin/ -lcutevariantcore

INCLUDEPATH += $$PWD/../cutevariantcore
DEPENDPATH += $$PWD/../cutevariantcore

INCLUDEPATH += $$PWD/../cutevariantcore/datamapper
DEPENDPATH += $$PWD/../cutevariantcore/datamapper

INCLUDEPATH += $$PWD/../cutevariantcore/reader
DEPENDPATH += $$PWD/../cutevariantcore/reader

PRE_TARGETDEPS += $$PWD/../bin/libcutevariantcore.a

DEFINES += EXEMPLE_PATH=\\\"$$PWD/../../exemples/vcf/\\\"
DEFINES += EXEMPLE_VCF_PATH=\\\"$$PWD/../../exemples/vcf/snpeff.example.vcf\\\"
DEFINES += EXEMPLE_VCF_GZ_PATH=\\\"$$PWD/../../exemples/vcf/snpeff.example2.vcf.gz\\\"


# KGZIP
unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive
}
