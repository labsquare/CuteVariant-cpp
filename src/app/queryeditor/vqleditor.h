#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <QtWidgets>
#include "vqlhighlighter.h"
#include "variantquery.h"

class VqlEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    VqlEditor(QWidget * parent = 0);

    /**
     * @brief isValid
     * @return true if the VQL is valid
     */
    bool isValid() const;
    /**
     * @brief vql
     * @return the query vql
     */
    QString toVql() const;

public Q_SLOTS:
    void setColumns(const QStringList& columns);
    void setTable(const QString& table);
    void setCondition(const QString& condition);




Q_SIGNALS:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent * e);

private:
    VqlHighlighter * mHighlighter;




};

#endif // QUERYEDITOR_H
