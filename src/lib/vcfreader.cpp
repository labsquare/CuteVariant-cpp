#include "vcfreader.h"
namespace vcfreader {
// ============== Record Class ========================================
Record::Record()
{

}

Record::Record(const QString &chrom,
               quint64 pos,
               const QString &id,
               const QString &ref,
               const QStringList &alt,
               quint64 qual,
               const QString &filter,
               const QVariantMap &infos,
               const QString &format,
               const QHash<QString, QVariantMap>& samples)
{
    mChrom = chrom;
    mPos = pos;
    mId = id;
    mRef = ref;
    mAlt = alt;
    mQual = qual;
    mFilter = filter;
    mInfos = infos;
    mFormat = format;
    mSamples = samples;
}

QStringList Record::alleles() const
{
    QStringList list;
    list<<ref()<<alt();
    return list;
}

quint64 Record::start() const
{
    return pos();
}

quint64 Record::end() const
{
    return pos() + alt().first().size();
}

bool Record::isSnp() const
{
    if (ref().size() > 1)
        return false;

    if (alt().size() > 1)
        return false;

    if (alt().first() == ".")
        return false;

    return true;


}




// ============== Field Class ========================================

QVariant::Type Field::typeFromString(const QString &type)
{
    QVariant::Type out = QVariant::String;

    if (type == "Integer")
        out = QVariant::Int;

    if (type == "Float")
        out = QVariant::Double;

    if (type == "Flag")
        out = QVariant::String;

    if (type == "Character")
        out = QVariant::String;

    if (type == "String")
        out = QVariant::String;

    return out;
}


// ============== VcfReader Class ========================================

VcfReader::VcfReader(QObject *parent)
    :QObject(parent)
{

}

VcfReader::VcfReader(const QString &filename, QObject *parent)
    :QObject(parent),mFilename(filename)
{
    mDevice = new QFile(filename);
}

VcfReader::VcfReader(QIODevice *device, QObject *parent)
    :QObject(parent),mDevice(device)
{


}

const QHash<QString, Field>& VcfReader::infos() const
{
    return mInfos;
}

const QHash<QString, Field> &VcfReader::formats() const
{
    return mFormats;
}

const QHash<QString, QVariant> &VcfReader::metadata() const
{
    return mMetadata;
}

bool VcfReader::open()
{
    if (mDevice->open(QIODevice::ReadOnly))
    {
        mStream.setDevice(mDevice);
        readHeader();
        return true;
    }

    return false;

}

bool VcfReader::next()
{

    if (mDevice->atEnd())
        return false;

    mCurrentRecord = readRecord(mStream.readLine());

    return true;
}

const Record &VcfReader::record() const
{
    return mCurrentRecord;
}

const QStringList &VcfReader::samples() const
{
    return mSamples;
}

void VcfReader::readHeader()
{
    mMetadata.clear();
    mInfos.clear();
    mFormats.clear();
    mSamples.clear();

    while (!mStream.atEnd())
    {
        QString line = mStream.readLine();

        // Get samples
        if (line.startsWith("#CHROM"))
        {
            QStringList header = line.split(QChar::Tabulation);
            if (header.size() > 9)
            {
                for (int i = 9 ; i< header.size(); ++i)
                    mSamples.append(header[i]);
            }
        }

        // get headers informations
        if (line.startsWith("##")){

            if (line.startsWith("##INFO"))
            {
                QRegularExpression ex("^##INFO=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+");
                QRegularExpressionMatch match = ex.match(line);
                Field info;
                info.id = match.captured(1);
                info.number = match.captured(2);
                info.type = match.captured(3);
                info.description = match.captured(4);
                mInfos.insert(info.id, info);
            }

            if (line.startsWith("##FORMAT"))
            {
                QRegularExpression ex("^##FORMAT=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+");
                QRegularExpressionMatch match = ex.match(line);
                Field format;
                format.id = match.captured(1);
                format.number = match.captured(2);
                format.type = match.captured(3);
                format.description = match.captured(4);
                if (match.hasMatch())
                    mFormats.insert(format.id, format);
            }



            if (line.contains(QRegularExpression("^##[^(INFO|ANN)]")))
            {
                QRegularExpression ex("^##(.+)=\"(.+)\"$");
                QRegularExpressionMatch match = ex.match(line);
                if (match.hasMatch())
                    mMetadata.insert(match.captured(1), match.captured(2));
            }



        }
        else {
            return;

        }
    }

}

Record VcfReader::readRecord(const QString &raw)
{
    QStringList row = raw.split(QChar::Tabulation);

    if (row.count() < 8){
        qWarning()<<Q_FUNC_INFO<<"not enough line. Are you sure it's a VCF?";
        return Record();
    }
    else {
        QString chrom   = row[0];
        quint64 pos     = row[1].toInt();
        QString id      = row[2];
        QString ref     = row[3];
        QString alt     = row[4];
        // Split alternative.. A,C => [A,C]
        QStringList alts;
        if (alt.contains(","))
            alts = alt.split(",");
        else
            alts.append(alt);

        quint64 qual    = row[5].toInt();
        QString filter  = row[6];
        // parse INFO
        QVariantMap infos;

        for (QString info : row[7].split(";"))
        {
            QStringList s = info.split("=");
            if (s.count() == 2)
            {
                QVariant val;
                // check if multi values
                if (s[1].contains(","))
                    val = s[1].split(",");
                else
                    val = s[1];
                infos.insert(s[0], val);
            }
        }

        // Parse samples if exists
        if (row.count() > 8)
        {
            QString format = row[8];
            QStringList items = format.split(":");
            QHash<QString, QVariantMap> samples;


            for (int i=9 ; i<row.size(); ++i)
            {
                QStringList sampleData = row[i].split(":");
                QVariantMap data;

                for (int j=0; j<sampleData.size(); ++j)
                    data.insert(items[j],sampleData[j]);

                samples.insert(mSamples.at(i-9), data);
            }

            return Record(chrom,pos, id, ref, alts, qual, filter,infos, format, samples);

        }
        else
            return Record(chrom,pos, id, ref, alts, qual, filter,infos);



    }
}
}
