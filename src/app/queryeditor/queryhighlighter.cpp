#include "queryhighlighter.h"

QueryHighlighter::QueryHighlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{



}

void QueryHighlighter::highlightBlock(const QString &text)
{

    QRegularExpression exp("(SELECT|FROM|WHERE|IN)");

    if (exp.match(text).hasMatch())
    {

        QRegularExpressionMatchIterator all = exp.globalMatch(text);
        while (all.hasNext())
        {
            QRegularExpressionMatch m = all.next();
            QFont font;
            font.setBold(true);
            setFormat(m.capturedStart(), m.capturedLength(),font);

        }


    }



}
