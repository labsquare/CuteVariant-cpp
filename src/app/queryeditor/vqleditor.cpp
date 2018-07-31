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
    return query().isValid();
}
//--------------------------------------------------------

cvar::VariantQuery VqlEditor::query() const
{
    return cvar::VariantQuery::fromVql(text());
}
//--------------------------------------------------------
void VqlEditor::setQuery(const cvar::VariantQuery &query)
{
    setText(query.toVql());
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


    for (const cvar::Field& field : cutevariant->fields())
    {
        api->add(field.colname().toLower());
    }
    api->prepare();
}
//--------------------------------------------------------
