#include <QtTest>

// add necessary includes here

class Variant : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();

};


void Variant::initTestCase()
{


}

void Variant::cleanupTestCase()
{

}


QTEST_APPLESS_MAIN(Variant)

#include "tst_variant.moc"
