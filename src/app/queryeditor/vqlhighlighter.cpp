#include "vqlhighlighter.h"

VqlHighlighter::VqlHighlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{



}

void VqlHighlighter::highlightBlock(const QString &text)
{

    QRegularExpression exp;
    QFont font;
    QTextCharFormat format;

    exp.setPattern("(SELECT|FROM|WHERE)");
    if (exp.match(text).hasMatch())
    {
        QRegularExpressionMatchIterator all = exp.globalMatch(text);
        while (all.hasNext())
        {
            QRegularExpressionMatch m = all.next();
            font.setBold(true);
            format.setFont(font);
            format.setForeground(QBrush(QColor("#000080")));
            setFormat(m.capturedStart(), m.capturedLength(),format);

        }


    }

    exp.setPattern("\\\".+\\\"");

    if (exp.match(text).hasMatch())
    {

        QRegularExpressionMatchIterator all = exp.globalMatch(text);
        while (all.hasNext())
        {
            QRegularExpressionMatch m = all.next();
            font.setBold(false);
            format.setFont(font);
            format.setForeground(QBrush(QColor("#ff9b00")));
            setFormat(m.capturedStart(), m.capturedLength(),format);
        }
    }

    exp.setPattern("(\\w+\\\.|sample)");

    if (exp.match(text).hasMatch())
    {
        QRegularExpressionMatchIterator all = exp.globalMatch(text);
        while (all.hasNext())
        {
            QRegularExpressionMatch m = all.next();
            font.setBold(true);
            format.setFont(font);
            format.setForeground(QBrush(QColor("#008080")));
            setFormat(m.capturedStart(), m.capturedLength(),format);
        }
    }




}
