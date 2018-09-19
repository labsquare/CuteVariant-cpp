#ifndef PROJECT_H
#define PROJECT_H
#include <QtCore>
#include <QtSql>
#include <QSettings>


#define cutevariant cvar::CuteVariant::i()

namespace cvar {
class QueryBuilder;
class VariantQueryBuilder;

class Variant;
class Field;
class Region;
class Sample;

class CuteVariant : public QObject
{
    Q_OBJECT
public:
    enum CompareMode {
        SiteMode ,
        VariantMode
    };

    ~CuteVariant();


    static CuteVariant * i();

    /*!
     * \brief setDatabasePath
     * set sqlite database path
     * \return
     */
    bool openDatabase(const QString& path);
    void closeDatabase();


    // samples

    /*!
     * \brief samples
     * \return samples list from sqlite
     */
  //  QList<Sample> samples() const;


    // fields
    /*!
     * \brief fields
     * \return variant fields from sqlite
     */
   // QList<Field> fields() const;
   // QList<Field> genotypeFields() const;

    // views
    /*!
     * \brief views
     * view are variant set store as a view sql
     * \return views
     */
   // QList<View> views() const;

    /*!
       * \brief views
       * view are variant set store as a view sql
       * \return views
       */
  //  bool addView(const View& view);



   // bool addViewFromExpression(const QString& name, const QString& expression, CompareMode mode = SiteMode);

    /*!
       * \brief removeView
       * remove views
       * \return views
       */
  //  bool removeView(const QString& name) const;
    /*!
       * \brief viewNames
       * Useless... ise views instead
       * \return return names of each view
       */
  //  QStringList viewNames() const;


    /*!
       * \brief variantsCount
       * \param table
       * \return how many variant from a specific set
       */
  //  int viewCount(const QString& view = "variants");



    // Variants

    /*!
       * \brief variant
       * \param variantId
       * \return a Variant from sql ID
       */
  //  Variant variant(int id) const;


    /*!
     * \brief variantsCount
     * \param query
     * \return how many variant for a specific VariantQuery
     */
    //int variantsCount(const VariantQuery& query) ;


  //  bool saveVariant(const Variant& variant);





    // metadatas
  //  QHash<QString, QVariant> metadatas() const;


    // bedfiles
    //TODO really useful ?
    //    QList<BedFile> bedFiles() const;



    // Links
   // QList<VariantLink> links() const;
   // bool setLinks(QList<VariantLink>& links);
   // bool removeLink(const VariantLink& link);
  //  bool addLink(VariantLink& link);



    // import

   // QFuture<bool> importFile(const QString& filename, VariantReaderFactory::Format format = VariantReaderFactory::Unknown);





   // SqliteManager *sqlite();

    // utils

    static QByteArray md5sum(const QString& filename);
    static QByteArray iconToData(const QIcon& icon);


    const QSqlDatabase& database() const;

Q_SIGNALS:
    void importRangeChanged(int min, int max);
    void importProgressChanged(int progress, const QString& message = QString());



private:
    CuteVariant(QObject * parent = nullptr);
    QSqlDatabase mSqlDb;
    static CuteVariant * mInstance;

   // Importer * mImporter;




};
}
#endif // PROJECT_H
