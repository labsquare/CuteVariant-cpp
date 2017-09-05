#ifndef QUERYHIGHLIGHTER_H
#define QUERYHIGHLIGHTER_H
#include <QtCore>
#include <QSyntaxHighlighter>

class VqlHighlighter : public QSyntaxHighlighter
{
public:
    VqlHighlighter(QTextDocument *parent = 0);


protected:
    virtual void highlightBlock(const QString& text) override;
};

#endif // QUERYHIGHLIGHTER_H
