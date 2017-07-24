#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QStandardItemModel>
#include <QtSql>
#include "project.h"

namespace core {
class ResultModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ResultModel(Project * prj, QObject * parent = nullptr);
    void setQuery(const QString& raw);

public Q_SLOTS:
    void load();

private:

    Project * mProject;
};
}
#endif // RESULTMODEL_H
