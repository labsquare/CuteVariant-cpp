#include "vqleditor.h"

VqlEditor::VqlEditor(QWidget * parent)
    :QPlainTextEdit(parent)
{
    mHighlighter = new VqlHighlighter(document());
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
    return toPlainText().simplified();
}
//--------------------------------------------------------
void VqlEditor::setColumns(const QStringList &columns)
{

}
//--------------------------------------------------------
void VqlEditor::setTable(const QString &table)
{

}
//--------------------------------------------------------
void VqlEditor::setCondition(const QString &condition)
{

}


//--------------------------------------------------------
void VqlEditor::keyPressEvent(QKeyEvent *e)
{

    if (e->modifiers() & Qt::ControlModifier)
    {

        if (e->key() == Qt::Key_Return)
            emit returnPressed();
    }
    return QPlainTextEdit::keyPressEvent(e);
}
//--------------------------------------------------------
