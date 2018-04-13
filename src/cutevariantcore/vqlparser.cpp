#include "vqlparser.h"

VqlParser::VqlParser(const QString &query)
    :mQuery(query)
{

}

const QString VqlParser::query() const
{
    return mQuery;
}

const QString VqlParser::tableName() const
{
    QRegularExpression exp("(?<=FROM)\\s(\\w+)");
    QRegularExpressionMatch match = exp.match(query());

    if ( match.isValid())
        return match.captured(1).simplified();

    return QString();
}

const QStringList VqlParser::columns() const
{
    QRegularExpression exp("(?<=SELECT)\\s((.+))\\s(?=FROM)");
    QRegularExpressionMatch match = exp.match(query());


    if (match.isValid()){
        QStringList out;

        for (QString i : match.captured(1).simplified().split(","))
            out.append(i.simplified());

        return out;
    }

    return QStringList();
}

const QString VqlParser::conditions() const
{
    QRegularExpression exp("(?<=WHERE)\\s(((?!REGION).)+)");
    QRegularExpressionMatch match = exp.match(query());
    if ( match.isValid())
        return match.captured(1).simplified();

    return QString();
}

const QString VqlParser::region() const
{
    QRegularExpression exp("(?<=REGION)\\s(\\w+)");
    QRegularExpressionMatch match = exp.match(query());
    if ( match.isValid())
        return match.captured(1).simplified();

    return QString();
}

const QStringList VqlParser::samples() const
{
    QStringList out;
    QRegularExpression exp("genotype\\(\"?(\\w+)\"?\\)");
    QRegularExpressionMatchIterator i = exp.globalMatch(query());

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();

        if (match.hasMatch())
            out.append(match.captured(1));


    }

    return out;

}

void VqlParser::setQuery(const QString &query)
{
    mQuery = query;
}

bool VqlParser::isValid() const
{
    return true;
}

