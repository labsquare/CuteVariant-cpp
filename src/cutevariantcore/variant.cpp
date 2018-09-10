#include "variant.h"

#define _binFirstShift 17       /* How much to shift to get to finest bin. */
#define _binNextShift 3         /* How much to shift to get to next larger bin. */
#define _binOffsetOldToExtended  4681
static QList<int> binOffsetsExtended ={4096+512+64+8+1, 512+64+8+1, 64+8+1, 8+1, 1, 0};
static QList<int> binOffsets = {512+64+8+1, 64+8+1, 8+1, 1, 0};

namespace cvar {
Variant::Variant(const QString &chr, quint64 pos, const QString &ref, const QString &alt)
    :mChr(chr), mPos(pos), mRef(ref), mAlt(alt)
{

}

void Variant::addAnnotation(const QString& colname, const QVariant &value)
{   
    mAnnotations.insert(colname, value);
}

void Variant::clearAnnotation()
{
    mAnnotations.clear();
}

void Variant::removeAnnotation(const QString &colname)
{
    mAnnotations.remove(colname);
}

QVariant Variant::annotation(const QString &colname) const
{
    return mAnnotations.value(colname,QVariant());
}

QVariant& Variant::operator[](const QString &colname)
{
    return mAnnotations[colname];
}

bool Variant::operator==(const Variant &v1)
{
    return name() == v1.name();
}

void Variant::setChr(const QString &chr)
{
    mChr = chr;
}

void Variant::setPos(quint64 pos)
{
    mPos = pos;
}

void Variant::setRef(const QString &ref)
{
    mRef = ref;
}

void Variant::setAlt(const QString &alt)
{
    mAlt = alt;
}

void Variant::setRsId(const QString &rsid)
{
    mRsId = rsid;
}

void Variant::setQual(double qual)
{
    mQual = qual;
}

bool Variant::isNull() const
{
    return chromosom().isEmpty();
}

QString Variant::name() const
{
    return QString("%1-%2-%3-%4").arg(chromosom()).arg(position()).arg(ref()).arg(alt());
}

QString Variant::coordinate() const
{
    return QString("%1:%2").arg(mChr).arg(mPos);
}

QString Variant::igvUrl() const
{
    return QString(QString("http://localhost:60151/locus?%1:%2").arg(chromosom()).arg(position()));
}

QString Variant::varsomeUrl() const
{
    return QString(QString("https://varsome.com/variant/hg19/%2").arg(name()));

}

void Variant::setFilter(const QString &filter)
{
    mFilter = filter;
}

const QString &Variant::chromosom() const
{
    return mChr;
}

quint64 Variant::position() const
{
    return mPos;
}

const QString& Variant::rsId() const
{
    return mRsId;
}

const QString& Variant::filter() const
{
    return mFilter;
}

double Variant::qual() const
{
    return mQual;
}

quint64 Variant::bin() const
{
    return mBin;
}

void Variant::setBin(quint64 bin)
{
    mBin = bin;
}


//int Variant::binFromRangeStandard(int start, int end)
//{
//    /* Given start,end in chromosome coordinates assign it
//     * a bin.   There's a bin for each 128k segment, for each
//     * 1M segment, for each 8M segment, for each 64M segment,
//     * and for each chromosome (which is assumed to be less than
//     * 512M.)  A range goes into the smallest bin it will fit in. */

//    int startBin = start, endBin = end-1, i;
//    startBin >>= _binFirstShift;
//    endBin >>= _binFirstShift;
//    for (i=0; i<binOffsets.size(); ++i)
//    {
//        if (startBin == endBin)
//            return binOffsets[i] + startBin;
//        startBin >>= _binNextShift;
//        endBin >>= _binNextShift;
//    }
//    qWarning()<<"start "<<start<<" end "<<end<<" out of range in findBin (max is 512M)";
//    return 0;

//}

//int Variant::binFromRangeExtended(int start, int end)
//{
//    /* Given start,end in chromosome coordinates assign it
//     * a bin.   There's a bin for each 128k segment, for each
//     * 1M segment, for each 8M segment, for each 64M segment,
//     * for each 512M segment, and one top level bin for 4Gb.
//     *      Note, since start and end are int's, the practical limit
//     *      is up to 2Gb-1, and thus, only four result bins on the second
//     *      level.
//     * A range goes into the smallest bin it will fit in. */

//    int startBin = start, endBin = end-1, i;
//    startBin >>= _binFirstShift;
//    endBin >>= _binFirstShift;
//    for (i=0; i<binOffsetsExtended.size(); ++i)
//    {
//        if (startBin == endBin)
//            return _binOffsetOldToExtended + binOffsetsExtended[i] + startBin;
//        startBin >>= _binNextShift;
//        endBin >>= _binNextShift;
//    }
//    qWarning()<<"start "<<start<<" end "<<end<<" out of range in findBin (max is 2Go)";

//    return 0;
//}

QList<int> Variant::ucscBins(int start, int end)
{
    QList<int> bins;

    int startBin = start >> _binFirstShift;
    int endBin = (end-1) >> _binFirstShift;

    for (int offset : binOffsets)
    {
        if (startBin == endBin)
            bins.append(startBin + offset);
        else {

            for (int i = startBin + offset; i < endBin + offset; ++i)
                bins.append(i);
        }

        startBin >>= _binNextShift;
        endBin >>= _binNextShift;
    }
    return bins;
}

int Variant::maxUcscBin(int start, int end)
{
    int bin = 0;
    int startBin = start >> _binFirstShift;
    int endBin = (end-1) >> _binFirstShift;

    for (int offset : binOffsets)
    {
        if (startBin == endBin){
            if (startBin + offset > bin)
                bin = startBin + offset;
        }

        else {
            for (int i=startBin + offset; i<endBin + offset; ++i)
            {
                if (i> bin)
                    bin = i;
            }
        }

        startBin >>= _binNextShift;
        endBin >>= _binNextShift;
    }
    return bin;
}

QHash<QString, QVariant> Variant::annotations() const
{
    return mAnnotations;
}

const QString& Variant::comment() const
{
    return mComment;
}

void Variant::setComment(const QString &comment)
{
    mComment = comment;
}

bool Variant::isFavoris() const
{
    return mIsFavoris;
}

void Variant::setFavoris(bool isFavoris)
{
    mIsFavoris = isFavoris;
}

int Variant::score() const
{
    return mScore;
}

void Variant::setScore(int score)
{
    mScore = score;
}

quint64 Variant::id() const
{
    return mId;
}

void Variant::setId(const quint64 &id)
{
    mId = id;
}


const QString &Variant::ref() const
{
    return mRef;
}

const QString &Variant::alt() const
{
    return mAlt;
}
}
