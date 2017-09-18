#include "vqleditor.h"
#include <QFontDatabase>

VqlEditor::VqlEditor(QWidget * parent)
    :QsciScintilla(parent)
{
    mLexer = new QsciLexerSQL(this);
    setMarginLineNumbers(1,true);
    setAutoCompletionThreshold(1);
    setAutoCompletionSource(QsciScintilla::AcsAPIs);
    setAutoCompletionCaseSensitivity(false);
    registerKeywords();
    setLexer(mLexer);


}
//--------------------------------------------------------
bool VqlEditor::isValid() const
{
    cvar::VariantQuery q = cvar::VariantQuery::fromVql(toVql());
    return q.isValid();
}
//--------------------------------------------------------

QString VqlEditor::toVql() const
{

    return text().simplified();
}
//--------------------------------------------------------
void VqlEditor::setVql(const QString &raw)
{
    setText(raw.simplified());
}
//--------------------------------------------------------
void VqlEditor::setVql(const QStringList &columns, const QString &table, const QString &condition)
{
    QString vql;

    if (!columns.isEmpty())
        vql+= QString("SELECT %1 ").arg(columns.join(","));

    if (!table.isEmpty())
        vql+= QString("FROM %2 ").arg(table);

    if (!condition.isEmpty())
        vql += QString("WHERE %3 ").arg(condition);

    setVql(vql);

}
//--------------------------------------------------------
void VqlEditor::reset()
{
    registerKeywords();
}
//--------------------------------------------------------
void VqlEditor::keyPressEvent(QKeyEvent *e)
{

    if (e->modifiers() & Qt::ControlModifier)
    {

        if (e->key() == Qt::Key_Return)
            emit returnPressed();
    }
    return QsciScintilla::keyPressEvent(e);
}
//--------------------------------------------------------
void VqlEditor::registerKeywords()
{
    QsciAPIs * api = new QsciAPIs(mLexer);

    api->add("SELECT");
    api->add("WHERE");
    api->add("FROM");


    for (const cvar::Field& field : cutevariant->sqliteManager()->fields())
    {
        api->add(field.colname().toLower());
    }



    api->prepare();
}
//--------------------------------------------------------
