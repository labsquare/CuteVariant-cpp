#include "importwizard.h"

ImportWizard::ImportWizard(QWidget *parent)
    :QWizard(parent)
{


    addPage(new ImportFilePage);
    addPage(new ImportProgressPage);
    //addPage(new ResumePage);

}
