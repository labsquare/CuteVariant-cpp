#ifndef FIELD_H
#define FIELD_H
#include <QtCore>
#include "datacolumn.h"
namespace cvar {

/*!
 * \brief The Field class contains Annotation description
 * @see sql field table
 */
class Field
{
public:


    Field(const QString& name = QString(),
          const QString& category = QString(),
          const QString& description = QString(),
          QVariant::Type type = QVariant::String);

    const QString& colname() const;
    const QString &name() const;
    const QString &description() const;
    QVariant::Type type() const;

    QString typeName() const;
    QString category() const;

    /*!
      * \brief simplified the string to save into sql
      * \param name
      * \return sql valid String
      */
    static QString simplified(const QString& name);

    void setColname(const QString& colname);
    void setName(const QString& name);
    void setDescription(const QString& description);
    void setType(QVariant::Type type);
    void setType(const QString& name);
    void setCategory(const QString& category);

    bool operator ==(const Field& other);
    bool isNull() const;

    QString expression() const;
    void setExpression(const QString &expression);

    quint64 id() const;
    void setId(const quint64 &id);

    static Field standardField(const QString& name);

private:
    QString mColname;
    QString mName;
    QString mDescription;
    QString mCategory;
    QString mExpression;
    QVariant::Type mType    = QVariant::String;
    quint64 mId;


//     QHash<QString, Field> STANDARD_FIELDS =
//    {

//        {"test", Field()}

//    };
//        {"allele",                 {"allele"        ,"ANN"         ,"reference alllele"          , QVariant::String}},
//        {"consequence",            {"consequence"   ,"ANN"         ,"consequence"                , QVariant::String}},
//        {"impact",                 {"impact"        ,"ANN"         ,"name of gene"               , QVariant::String}},
//        {"gene_name",              {"gene_name"     ,"ANN"         ,"gene iD"                    , QVariant::String}},
//        {"gene_id",                {"gene_id"       ,"ANN"         ,"impact"                     , QVariant::String}},
//        {"feature_type",           {"feature_type"  ,"ANN"         ,"impact"                     , QVariant::String}},
//        {"feature_id",             {"feature_id"    ,"ANN"         ,"impact"                     , QVariant::String}},
//        {"biotype",                {"biotype"       ,"ANN"         ,"impact"                     , QVariant::String}},
//        {"hgvs_p",                 {"hgvs_p"        ,"ANN"         ,"impact"                     , QVariant::String}},
//        {"hgvs_c",                 {"hgvs_c"        ,"ANN"         ,"impact"                     , QVariant::String}},



};




}
#endif // FIELD_H
