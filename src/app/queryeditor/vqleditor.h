#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <QtWidgets>
#include "vqlhighlighter.h"
#include "variantquery.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qsciapis.h>
#include "cutevariant.h"

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
    cvar::VariantQuery query() const;
    void setQuery(const cvar::VariantQuery& query);

    void reset();



Q_SIGNALS:
    void returnPressed();

protected:
    void keyPressEvent(QKeyEvent * e);
    void registerKeywords();


private:
    QsciLexerSQL * mLexer;





};

#endif // QUERYEDITOR_H
