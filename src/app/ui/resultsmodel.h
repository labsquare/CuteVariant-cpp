#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QStandardItemModel>
#include <QtSql>
#include "project.h"

class ResultsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ResultsModel(core::Project * prj, QObject * parent = nullptr);
    void setQuery(const QString& raw);

    int totalVariantCount() const;

public Q_SLOTS:
    void load(int offset = 0, int limit = 100);

private:

    core::Project * mProject;
};

#endif // RESULTMODEL_H
