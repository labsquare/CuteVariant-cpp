#ifndef QUERYHIGHLIGHTER_H
#define QUERYHIGHLIGHTER_H
#include <QtCore>
#include <QSyntaxHighlighter>

class QueryHighlighter : public QSyntaxHighlighter
{
public:
    QueryHighlighter(QTextDocument *parent = 0);


protected:
    virtual void highlightBlock(const QString& text) override;
};

#endif // QUERYHIGHLIGHTER_H
