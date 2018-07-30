#ifndef PROJECT_H
#define PROJECT_H
#include <QtCore>
#include <QtSql>
#include <QSettings>
#include "variantlink.h"
#include "view.h"
#include "sqlitemanager.h"
#include "importer.h"

#define cutevariant cvar::CuteVariant::i()

namespace cvar {
class QueryBuilder;
class SqliteManager;
class CuteVariant
{
public:
    ~CuteVariant();


    static CuteVariant * i();

    void setDatabasePath(const QString& path);


    // samples

    /*!
     * \brief samples
     * \return samples list from sqlite
     */
    QList<Sample> samples() const;


    // fields
    /*!
     * \brief fields
     * \return variant fields from sqlite
     */
    QList<Field> fields() const;
    QList<Field> genotypeFields() const;

    // views
    /*!
     * \brief views
     * view are variant set store as a view sql
     * \return views
     */
    QList<View> views() const;

    /*!
       * \brief views
       * view are variant set store as a view sql
       * \return views
       */
    bool addView(const View& view);

    /*!
       * \brief removeView
       * remove views
       * \return views
       */
    bool removeView(const QString& name) const;
    /*!
       * \brief viewNames
       * Useless... ise views instead
       * \return return names of each view
       */
    QStringList viewNames() const;


    /*!
       * \brief variantsCount
       * \param table
       * \return how many variant from a specific set
       */
    int viewCount(const QString& view = "variants");



    // Variants

    /*!
       * \brief variant
       * \param variantId
       * \return a Variant from sql ID
       */
    Variant variant(int id) const;


    // metadatas
    QHash<QString, QVariant> metadatas() const;



    // Links
    QList<VariantLink> links() const;
    bool setLinks(QList<VariantLink>& links);
    bool removeLink(const VariantLink& link);
    bool addLink(VariantLink& link);




    Importer *importer();



    SqliteManager *sqlite();

    // utils

    static QByteArray md5sum(const QString& filename);
    static QByteArray iconToData(const QIcon& icon);



private:
    CuteVariant();
    QSqlDatabase mSqlDb;
    static CuteVariant * mInstance;

    Importer * mImporter;

    SqliteManager * mSqliteManager;



};
}
#endif // PROJECT_H
