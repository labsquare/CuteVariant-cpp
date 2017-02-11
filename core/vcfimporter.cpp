#include "vcfimporter.h"

VcfImporter::VcfImporter(QObject * parent)
    :QThread(parent)
{
    QSqlQuery mVariantQuery;
    mVariantQuery.prepare("INSERT INTO variants (chrom, pos, ref, alt) "
                  "VALUES (:chrom, :pos, :ref, :alt)");


}

void VcfImporter::setFileNames(const QStringList &paths)
{
    mPaths = paths;
}

void VcfImporter::run()
{
    QTime start = QTime::currentTime();

    // Parsing VCF Files
    QSqlDatabase::database().transaction();

    for (QString path : mPaths)
    {
        QFile file(path);
        // insert filename
        int fileID = insertFilename(file);

        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QString line;
            while(stream.readLineInto(&line))
            {
                //======= PARSE HEADER ================================
                if (line.startsWith("#"))
                {

                    // PARSE ANNOTATION FIELD NAME
                    if (line.startsWith("##INFO"))
                    {
                        // example : ##INFO=<ID=H2,Number=0,Type=Flag,Description="HapMap2 membership">
                        QString info = line.replace("##INFO=","");
                        QRegularExpression ex("<ID=(\\w+).+Type=(\\w+).+Description=\"(.+)\".+");
                        QRegularExpressionMatch match = ex.match(info);
                        Field field(match.captured(1), match.captured(3));
                        if (field.name() != "ANN")
                            mInfoFields.append(field);

                    }

                    if (line.startsWith("##FORMAT"))
                    {
                        // example : ##FORMAT=<ID=SRR,Number=1,Type=Integer,Description="Number of reference observations on the reverse strand">
                        QString info = line.replace("##FORMAT=","");
                        QRegularExpression ex("<ID=(\\w+).+Type=(\\w+).+Description=\"(.+)\".+");
                        QRegularExpressionMatch match = ex.match(info);
                        Field field(match.captured(1), match.captured(3));
                        if (field.name() != "ANN")
                            mFormatFields.append(field);
                    }

                    // PARSE SAMPLES
                    if (line.startsWith("#CHROM"))
                    {
                        QStringList row = line.split(QChar::Tabulation);
                        if (row.size()<9){
                            qDebug()<<"No sample defined";
                            insertSample("default",fileID);
                        }
                        else
                            for (int i=9; i<row.size(); ++i)
                            {
                                QString sample = row[i];
                                insertSample(sample, fileID);
                            }
                    }

                }
                //======= PARSE CONTENT ================================
                else
                {
                    // When Header has been completed parsed, install SQL
                    if (!mHeaderParsed)
                    {
                        insertFields(mFormatFields);
                        insertFields(mInfoFields);
                        mHeaderParsed = true;
                    }

                    // Parse variant
                    QStringList row = line.split(QChar::Tabulation);
                    QString chrom = row.at(0);
                    quint64 pos = row.at(1).toInt();
                    QString ref = row.at(3);
                    QString alt = row.at(4);
                    QString info = row.at(7);

                    // insert variant
                    int variantID = insertVariant(chrom, pos, ref,alt);

                    // parse info
                    QStringList infos = info.split(";");
                    for (QString s : infos)
                    {
                        QStringList pair = s.split("=");
                        if (pair.count() == 2){
                            QString key  = pair.at(0);
                            QVariant val = pair.at(1);
                            int fieldID  = infoField(key).id();
                            // insert annotation
                            insertAnnotation(variantID, fieldID, val);


                        }
                    }





                }
            }
        }
    }

    QSqlDatabase::database().commit();

    qDebug()<<"parsing done "<< QTime::currentTime().secsTo(start);

    for (Field f : mFormatFields)
        qDebug()<<f.name()<<" "<<f.id();
}

int VcfImporter::insertVariant(const QString &chrom, quint64 pos, const QString &ref, const QString &alt)
{
    QSqlQuery query;
    query.prepare("INSERT INTO variants (chrom, pos, ref, alt) "
                  "VALUES (:chrom, :pos, :ref, :alt)");

    query.bindValue(":chrom", chrom);
    query.bindValue(":pos", pos);
    query.bindValue(":ref", ref);
    query.bindValue(":alt", alt);

    if (!query.exec())
        qDebug()<<query.lastError().text();

    return query.lastInsertId().toInt();

}

int VcfImporter::insertSample(const QString &sample, int fileID)
{
    QSqlQuery query;
    query.prepare("INSERT INTO samples (name, filename_id) "
                  "VALUES (:name, :filename_id)");

    query.bindValue(":name", sample);
    query.bindValue(":filename_id",fileID);

    if (!query.exec())
        qDebug()<<query.lastError().text();

    return query.lastInsertId().toInt();
}

int VcfImporter::insertFilename(const QFile &file)
{
    QSqlQuery query;
    query.prepare("INSERT INTO filenames (filename) "
                  "VALUES (:filename)");

    query.bindValue(":filename", file.fileName());

    if (!query.exec())
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();

    return query.lastInsertId().toInt();

}

void VcfImporter::insertFields(QList<Field> &fields)
{

    for (int i=0; i<fields.count(); ++i)
    {
        // TODO fields type
        QSqlQuery query;
        query.prepare("INSERT INTO fields (name, description) "
                      "VALUES (:name, :description)");

        query.bindValue(":name", fields[i].name());
        query.bindValue(":description", fields[i].description());

        if (!query.exec())
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();

        else
            fields[i].setId(query.lastInsertId().toInt());

    }


}

int VcfImporter::insertAnnotation(int variantID, int fieldID, const QVariant &value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO annotations (field_id, variant_id, value) "
                  "VALUES (:field_id, :variant_id, :value)");

    query.bindValue(":field_id", fieldID);
    query.bindValue(":variant_id", variantID);
    query.bindValue(":value", value);

    if (!query.exec())
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();

    return query.lastInsertId().toInt();

}

QList<Field> VcfImporter::parseHeader_ANN(const QString &description)
{
    /* See specification
     http://snpeff.sourceforge.net/VCFannotationformat_v1.0.pdf
     It must have 16 columns in DESCRIPTION Header <ID=ANN> .
     Seems columns have not always same names.. So I m gonna use those following

     - allele
     - annotation
     - putative_impact
     - gene_name
     - gene_id
     - feature_type
     - feature_id
     - transcipt_biotype
     - rank
     - hgvs_c
     - hgvs_p
     - cDNA_position / cdna_len
     - cds_postition / cds_len
     - protein_position / protein_len
     - distance
     - message
    */


    QList<Field> newFields;

    //    QRegularExpression reg(".+\'(.+)'");
    //    QRegularExpressionMatch match = reg.match(description);

    //    if (match.capturedLength() > 2)
    //    {
    //        QStringList rawFields = match.captured(1).split("|");
    //        if (rawFields.count() <16)
    //        {
    //            qDebug()<<Q_FUNC_INFO<<"Not enough column according specification of ANN";
    //            return newFields;
    //        }

    //    newFields.append(Field(tr("allele"), tr("")));




    //    }

    //    else
    //        qDebug()<<Q_FUNC_INFO<<"Cannot capture ANN Field";

    return newFields;
}

Field VcfImporter::infoField(const QString &name) const
{
    for (Field f : mInfoFields)
    {
        if (f.name() == name)
            return f;
    }
    return Field();
}


