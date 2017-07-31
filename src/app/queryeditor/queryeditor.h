#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <QtWidgets>
#include "queryhighlighter.h"
class QueryEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    QueryEditor(QWidget * parent = 0);


Q_SIGNALS:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent * e);



private:
    QueryHighlighter * mHighlighter;
};

#endif // QUERYEDITOR_H
