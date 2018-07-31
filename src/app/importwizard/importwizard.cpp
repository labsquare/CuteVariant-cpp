#include "importwizard.h"

ImportWizard::ImportWizard(QWidget *parent)
    :QWizard(parent)
{

    setWindowTitle(tr("Import file"));
    addPage(new ImportFilePage);
    addPage(new ImportProgressPage);
    //addPage(new ResumePage);

}
