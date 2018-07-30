#ifndef IMPORTWIZARD_H
#define IMPORTWIZARD_H
#include <QWizard>

#include "importfilepage.h"
#include "importprogresspage.h"
#include "resumepage.h"

class ImportWizard : public QWizard
{
public:
    ImportWizard(QWidget * parent = nullptr);


};

#endif // IMPORTWIZARD_H
