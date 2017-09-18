#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <QtWidgets>
#include "vqlhighlighter.h"
#include "variantquery.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexersql.h>

class VqlEditor : public QsciScintilla
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

    void setVql(const QString& raw);
    void setVql(const QStringList& columns, const QString& table, const QString& condition);





Q_SIGNALS:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent * e);


private:
    QsciLexerSQL * mLexer;




};

#endif // QUERYEDITOR_H
