#ifndef DATACOLUMN_H
#define DATACOLUMN_H
#include <QtCore>
namespace cvar {
class DataColumn
{
public:

    enum Type {
        Integer,
        Real,
        Text,
        Blob
    };

    DataColumn(const QString& name = QString("default"),  DataColumn::Type type =  DataColumn::Text, const QString& option = QString())
        :mName(name), mType(type), mOption(option) {}

    QString toSql() const {
        return QString("%1 %2 %3").arg(mName, typeToName(mType),mOption);
    }

    static QString typeToName(DataColumn::Type type)
    {
        switch (type)
        {
        case  DataColumn::Integer: return "INTEGER";
        case DataColumn::Real: return "REAL";
        case DataColumn::Text: return "TEXT";
        case DataColumn::Blob: return "BLOB";
        default: return "TEXT";
        }
    }

    static DataColumn::Type typeFromName(const QString& name)
    {
        if (name == "INTEGER")
            return DataColumn::Integer;

        if (name == "REAL")
            return DataColumn::Real;

        if (name == "TEXT")
            return DataColumn::Text;

        if (name == "BLOB")
            return DataColumn::Blob;

        return DataColumn::Text;
    }

    static DataColumn::Type typeFromQt(QVariant::Type type)
    {
        switch (type)
        {
        case QVariant::Int: return DataColumn::Integer;
        case QVariant::Double : return DataColumn::Real;
        case QVariant::String: return DataColumn::Text;
        default: return DataColumn::Text;
        }
    }


    QString name() const { return mName ;}

    DataColumn::Type type() const {return mType;}

    QString option() const {return mOption;}

private:

    QString mName;
    DataColumn::Type mType;
    QString mOption;

};

}

#endif // DATACOLUMN_H
