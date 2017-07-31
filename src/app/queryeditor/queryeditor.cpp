#include "queryeditor.h"

QueryEditor::QueryEditor(QWidget * parent)
    :QPlainTextEdit(parent)
{
    mHighlighter = new QueryHighlighter(document());
}

void QueryEditor::keyPressEvent(QKeyEvent *e)
{

    if (e->modifiers() & Qt::ControlModifier)
    {

        if (e->key() == Qt::Key_Return)
            emit returnPressed();
    }


    return QPlainTextEdit::keyPressEvent(e);


}
