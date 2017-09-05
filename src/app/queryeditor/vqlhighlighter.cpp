#include "vqlhighlighter.h"

VqlHighlighter::VqlHighlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{



}

void VqlHighlighter::highlightBlock(const QString &text)
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
