#include "vcfimporter.h"



// SUB PARSER ===============================================

void SubParser::addField(const Field &field)
{
    mHeaders.insert(field.name(), field);
}

void SubParser::setValue(const QString &fieldName, const QVariant &value)
{
    if (mHeaders.keys().contains(fieldName))
        mValues.insert(fieldName, value);
}

QList<Field> SubParser::fields() const
{
    return mHeaders.values();
}

void AnnSubParser::parseHeader(const QString &desc)
{
    QString raw = desc;
    // extract names
    QStringList ann;
    raw = raw.remove(QRegularExpression("^.+:"));
    for (QString s:raw.split("|"))
    {
        s = s.trimmed();
        s = s.remove("'");
        ann.append(s);
    }

    for ( QString s : ann)
    {
        addField(Field(s));
    }
}



void DefaultParser::parseHeader(const QString &line)
{

}


// VCF IMPORTER ==============================================


VcfImporter::VcfImporter(QObject * parent)
    :QThread(parent)
{

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

    // Loop over each files
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
                        QString id   = match.captured(1);
                        QString type = match.captured(2);
                        QString desc = match.captured(3);

                        if (mSubParsers.keys().contains(id))
                            mSubParsers[id]->parseHeader(desc);



                    }

                    if (line.startsWith("##FORMAT"))
                    {
                        // example : ##FORMAT=<ID=SRR,Number=1,Type=Integer,Description="Number of reference observations on the reverse strand">
                        QString info = line.replace("##FORMAT=","");
                        QRegularExpression ex("<ID=(\\w+).+Type=(\\w+).+Description=\"(.+)\".+");
                        QRegularExpressionMatch match = ex.match(info);
                        Field field(match.captured(1), match.captured(3));
                        mFormatFields.append(field);

                    }

                    // PARSE SAMPLES
                    if (line.startsWith("#CHROM"))
                    {
                        QStringList row = line.split(QChar::Tabulation);
                        if (row.size()<9){
                            qDebug()<<"No sample defined";
                            //insertSample("default",fileID);
                        }
                        else
                            for (int i=9; i<row.size(); ++i)
                            {
                                QString sample = row[i];
                                //insertSample(sample, fileID);
                            }
                    }

                }
                //======= PARSE CONTENT ================================
                else
                {
                    // When Header has been completed parsed, install SQL
                    if (!mHeaderParsed)
                    {

                        for (Field f : mInfoFields)
                            qDebug()<<f.name()<<" "<<f.id();

                        createAnnotationTable();
                        mHeaderParsed = true;
                        QSqlDatabase::database().commit();
                    }

                    // Parse variant
                    QStringList row = line.split(QChar::Tabulation);
                    QString chrom   = row.at(0);
                    quint64 pos     = row.at(1).toInt();
                    QString ref     = row.at(3);
                    QString alt     = row.at(4);
                    QString info    = row.at(7);

                    // insert variant
                    int variantID = insertVariant(chrom, pos, ref,alt);

                    // parse info

//                    QHash<QString, QVariant> annotations = parseInfo(info);
//                    insertAnnotation(variantID, annotations);
                }
            }
        }
    }

    QSqlDatabase::database().commit();


    qDebug()<<"parsing done "<< start.secsTo(QTime::currentTime())<<" sec";


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
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();

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

int VcfImporter::insertAnnotation(int variantID, const QHash<QString, QVariant> &annotations)
{
    QSqlQuery query;
    QStringList values;
    // add quote
    for (QVariant val : annotations.values()){
        QString s = val.toString();
        s = s.replace("'","");
        values.append(QString("'%1'").arg(s));

    }

    QString req = QString("INSERT INTO annotations (variant_id,%1) VALUES (%2,%3)")
            .arg(annotations.keys().join(","))
            .arg(variantID)
            .arg(values.join(","));


    bool ret = query.exec(req);
    if (!ret)
    {
        qDebug()<<query.lastQuery();
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();
    }


}


void VcfImporter::createAnnotationTable()
{
    qDebug()<<"create annotation table";
    QSqlQuery query;
    // Create table if not exists
    if (!QSqlDatabase::database().tables().contains("annotations"))
    {

        query.prepare("CREATE TABLE `annotations`("
                      "`id`  INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`bin` INTEGER DEFAULT 0,"
                      "`variant_id` INTEGER,"
                      "FOREIGN KEY(`variant_id`) REFERENCES variants(`id`))"
                      );

        if (!query.exec())
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();

        if(!query.exec("CREATE INDEX idx_annotation ON annotations(`id`)"))
            qDebug()<<Q_FUNC_INFO<<query.lastError().text();

    }

    // Combine all fields
    QList<Field> allFields ;
    allFields.append(mInfoFields);
    for (SubParser * parser  : mSubParsers)
        allFields.append(parser->fields());

    // Write all fields
    for (Field f : allFields)
    {
        QSqlQuery fquery;
        fquery.prepare("INSERT INTO fields (name, description,type) "
                       "VALUES (:name, :description, :type)");

        fquery.bindValue(":name", f.name());
        fquery.bindValue(":description", f.description());
        fquery.bindValue(":type", f.sqlType());

        if (!fquery.exec())
            qDebug()<<Q_FUNC_INFO<<fquery.lastError().text()<<fquery.lastQuery();
    }

    QSqlQuery alterQuery;
    for (int i=0; i<allFields.size(); ++i)
    {
       QString label = QString("ann_%1").arg(i+1);

            bool ret = alterQuery.exec(QString("ALTER TABLE `annotations` ADD COLUMN %1 %2")
                                       .arg(label)
                                       .arg(allFields.at(i).sqlType())
                                       );
            if (!ret)
                qDebug()<<Q_FUNC_INFO<<alterQuery.lastError().text();


    }
}


QList<Field> VcfImporter::parseInfoHeader(const QString &line)
{

}

QList<QVariant> VcfImporter::parseInfo(const QString &info)
{
    QList<QVariant> annotations;

//    // PARSE INFO FIELDS
//    QHash<QString, QVariant> infoHash;
//    for (QString s : info.split(";"))
//    {
//        QStringList pair = s.split("=");
//        if (pair.count() == 2){
//            QString key  = pair.at(0);
//            QVariant val = pair.at(1);
//            infoHash[key] = val;
//        }
//    }

//    for (Field f : mInfoFields)
//    {

//        if (infoHash.keys().contains(f.name()))
//            annotations[f.name()] = infoHash[f.name()];
//    }

    return annotations;

}


QStringList VcfImporter::tableColumnNames(const QString &tableName) const
{
    QSqlQuery query;
    QStringList names;
    query.prepare(QString("PRAGMA table_info(`%1`)").arg(tableName));
    if (!query.exec())
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();

    while(query.next())
        names.append(query.record().value("name").toString());

    return names;


}



