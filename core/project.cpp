#include "project.h"

Project::Project(const QString &databasePath, QObject *parent): QObject(parent)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    setDatabasePath(databasePath);

    if (!mDb.open())
        qDebug()<<"cannot open database";

}

void Project::setDatabasePath(const QString &filename)
{
    mDb.setDatabaseName(filename);
}

bool Project::createSchema()
{
    /**
     * @brief executeQueryFile
     * Read a query file and removes some unnecessary characters/strings such as comments,
     * and executes queries.
     * If there is possible to use Transaction, so this method will uses it.
     * Use this gist as MIT License.
     * EXCEPTION:
     *      Feel free to use this gist as you like without any restriction,
     *      if you or your country are a member of The Axis of Resistance
     *      (Iran + Syria + Lebanon + Russia + Iraq + Yemen + Bahrain + Palestine)
     * ~~ S.M. Mousavi - 2017 ~~
     */

    QFile file(":/files/schema.sql");
    if (file.open(QIODevice::ReadOnly))
    {
        QString queryStr(file.readAll());

        //Replace comments and tabs and new lines with space
        queryStr = queryStr.replace(QRegularExpression("(\\/\\*(.|\\n)*?\\*\\/|^--.*\\n|\\t|\\n)", QRegularExpression::CaseInsensitiveOption|QRegularExpression::MultilineOption), " ");
        //Remove waste spaces
        queryStr = queryStr.trimmed();

        //Extracting queries
        QStringList qList = queryStr.split(';', QString::SkipEmptyParts);

        //Initialize regular expression for detecting special queries (`begin transaction` and `commit`).
        //NOTE: I used new regular expression for Qt5 as recommended by Qt documentation.
        QRegularExpression re_transaction("\\bbegin.transaction.*", QRegularExpression::CaseInsensitiveOption);
        QRegularExpression re_commit("\\bcommit.*", QRegularExpression::CaseInsensitiveOption);

        //Check if query file is already wrapped with a transaction
        bool isStartedWithTransaction = re_transaction.match(qList.at(0)).hasMatch();
        if(!isStartedWithTransaction)
            mDb.transaction();     //<=== not wrapped with a transaction, so we wrap it with a transaction.

        //Execute each individual queries
        foreach(const QString &s, qList) {
            if(re_transaction.match(s).hasMatch())    //<== detecting special query
                mDb.transaction();
            else if(re_commit.match(s).hasMatch())    //<== detecting special query
                mDb.commit();
            else {
                QSqlQuery query;
                query.exec(s);                        //<== execute normal query
                if(query.lastError().type() != QSqlError::NoError) {
                    qDebug() << query.lastError().text();
                    mDb.rollback();                    //<== rollback the transaction if there is any problem
                    return false;
                }
            }
        }
        if(!isStartedWithTransaction)
            mDb.commit();          //<== ... completing of wrapping with transaction

    }
    return true;

}
