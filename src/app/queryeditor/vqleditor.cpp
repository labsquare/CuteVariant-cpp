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
void VqlEditor::setVql(const QString &raw)
{
    setPlainText(raw.simplified());
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
