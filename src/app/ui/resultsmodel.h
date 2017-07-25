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

    int variantCount() const;

public Q_SLOTS:
    void load();

private:

    core::Project * mProject;
};

#endif // RESULTMODEL_H
