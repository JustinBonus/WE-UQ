
#include "CFDExpertWidget.h"
#include <QFormLayout>
#include <QComboBox>
#include <QDir>
#include <QStandardPaths>
#include "RemoteCaseSelector.h"
#include "PatchesSelector.h"
#include <QDialog>
#include <usermodeshapes.h>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollArea>
#include <QResizeEvent>
#include <QFile>
#include <QTextStream>
#include <QVector>

#include "OpenFoamHelper/openfoamhelper.h"

CFDExpertWidget::CFDExpertWidget(RandomVariablesContainer *theRandomVariableIW, RemoteService* remoteService, QWidget *parent)
    : SimCenterAppWidget(parent), remoteService(remoteService), shown(false)
{
    inflowWidget    = new InflowParameterWidget(theRandomVariableIW, true);

    initializeUI();

    setupConnections();

    originalUFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/WE-UQ/U.orig";
    originalControlDictPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/WE-UQ/controlDict.orig";
    originalfvSolutionPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/WE-UQ/fvSolution.orig";
}

bool CFDExpertWidget::outputAppDataToJSON(QJsonObject &jsonObject)
{
    jsonObject["EventClassification"]="Wind";
    jsonObject["Application"] = "CFDEvent";
    QJsonObject dataObj;
    dataObj["OpenFOAMCase"]  = caseEditBox->text();

    QString openFOAMsolver = solverComboBox->currentText();
    if (openFOAMsolver.trimmed().toLower() == "pimplefoam") {
        dataObj["OpenFOAMSolver"] = "newPimpleFoam";
    }
    else {
        dataObj["OpenFOAMSolver"] = openFOAMsolver;
    }

    jsonObject["ApplicationData"] = dataObj;
    return true;
}

bool CFDExpertWidget::outputToJSON(QJsonObject &eventObject)
{
    inflowWidget->outputToJSON(eventObject);
    eventObject["OpenFOAMCase"]     = caseEditBox->text();
    eventObject["LengthScale"]      = lengthScale->value();
    eventObject["VelocityScale"]    = velocityScale->value();
    eventObject["OpenFOAMSolver"]   = solverComboBox->currentText();
    eventObject["InflowConditions"] = (inflowCheckBox->checkState() == Qt::CheckState::Checked);
    eventObject["type"]             = "ExpertCFD";
    eventObject["forceCalculationMethod"] = forceComboBox->currentText();
    eventObject["start"]            = startTimeBox->value();
    eventObject["patches"]          = patchesEditBox->text();
    eventObject["meshing"]          = meshingComboBox->currentData().toString();
    eventObject["processors"]       = processorsBox->value();
    eventObject["userModesFile"]    = couplingGroup->fileName();
    eventObject["FSIboundaryName"]  = couplingGroup->FSIboundarySelection();

    return true;
}

bool CFDExpertWidget::inputFromJSON(QJsonObject &eventObject)
{
  if(remoteService->isLoggedIn()) {

    loginRequiredLabel->hide();
	  
    if(eventObject.contains("OpenFOAMCase"))
      caseEditBox->setText(eventObject["OpenFOAMCase"].toString());

    this->setEnabled(true);
    this->downloadRemoteCaseFiles();

    if(eventObject.contains("LengthScale")) {
        lengthScale->setValue(eventObject["LengthScale"].toDouble());
    }
    else {
        lengthScale->setValue(1.00);
    }

    if(eventObject.contains("VelocityScale")) {
        velocityScale->setValue(eventObject["VelocityScale"].toDouble());
    }
    else {
        velocityScale->setValue(1.00);
    }
    
    if(eventObject.contains("OpenFOAMSolver"))
      solverComboBox->setCurrentText(eventObject["OpenFOAMSolver"].toString());
    
    if(eventObject.contains("InflowConditions"))
      inflowCheckBox->setChecked(eventObject["InflowConditions"].toBool());

    if(eventObject.contains("start"))
      this->startTimeBox->setValue(eventObject["start"].toDouble());

    if(eventObject.contains("forceCalculationMethod"))
        this->forceComboBox->setCurrentText(eventObject["forceCalculationMethod"].toString());

    if(eventObject.contains("patches"))
        this->patchesEditBox->setText(eventObject["patches"].toString());

    if(eventObject.contains("meshing"))
    {
        int index = meshingComboBox->findData(eventObject["meshing"].toString());
        if(index >= 0)
            this->meshingComboBox->setCurrentIndex(index);
    }

    if(eventObject.contains("processors"))
        this->processorsBox->setValue(eventObject["processors"].toInt());

    if(eventObject.contains("userModesFile"))
        this->couplingGroup->setFileName(eventObject["userModesFile"].toString());

    if(eventObject.contains("FSIboundaryName"))
        this->couplingGroup->setFSIboundarySelection(eventObject["FSIboundaryName"].toString());

    inflowWidget->inputFromJSON(eventObject);

  } else {
    loginRequiredLabel->show();
    
    errorMessage("For CFD Expert you need to be logged into DsaignSafe before input (Login button top right)");    
    return false;
  }

  return true;
}

bool CFDExpertWidget::copyFiles(QString &path)
{
    if (inflowCheckBox->isChecked() || couplingGroup->isChecked())
    {
        QDir targetDir(path);

        QDir constantDir(targetDir.filePath(""));
        targetDir.mkpath("0");
        targetDir.mkpath("system");

        auto newUPath = targetDir.filePath("0/U");
        if(QFile::exists(newUPath))
            QFile::remove(newUPath);

        QFile::copy(originalUFilePath, newUPath);

        auto newControlDictPath = targetDir.absoluteFilePath("system/controlDict");
        if(QFile::exists(newControlDictPath))
            QFile::remove(newControlDictPath);

        QFile::copy(originalControlDictPath, newControlDictPath);

        auto newfvSolutionPath = targetDir.absoluteFilePath("system/fvSolution");
        if(QFile::exists(newfvSolutionPath))
            QFile::remove(newfvSolutionPath);

        QFile::copy(originalfvSolutionPath, newfvSolutionPath);

        //return inflowWidget->copyFiles(path);
        return this->buildFiles(path);
    }

    return true;
}

bool CFDExpertWidget::buildFiles(QString &dirName)
{
    /*
     *  !!! this method replaces inflowWidget->copyFiles(path); !!!
     *
     * The change was necessary since both InFlowWidget and UserModeShapes
     * require modifications to the U and controlDict files
     *
     */

    // time to export :)

    // we place new files into the existing file structure
    // but we do save one version of the existing file as
    // filename.orig before writing the new one

    //
    // ... dynamicMeshDict file
    //

    if (couplingGroup->isChecked()) {

        newLocation = QDir(dirName);
        if (!newLocation.cd("constant")) {
            newLocation.mkdir("constant");
            newLocation.cd("constant");
        }

        QString newFile = newLocation.absoluteFilePath("dynamicMeshDict");
        QString origFile = newFile + ".orig";

        if (QFile(origFile).exists()) {
            qWarning() << "overwriting " << origFile;
            QFile::remove(origFile);
        }
        QFile::rename(newFile, origFile);

        qDebug() << "move" << newFile << origFile;

        // load template file
        QString sourceFile = couplingGroup->fileName();

        if (sourceFile.isEmpty())
            sourceFile = ":/Resources/CWE/Templates/dynamicMeshDict";
        QFile source(sourceFile);

        if (source.exists()) {
            source.copy(newFile);
        }
        else {
	  QString errorMsg = "Source file for dynamicMeshDict: \"" + sourceFile + "\" is missing";
	  errorMessage(errorMsg);
        }
    }

    //
    // ... generalizedMotionState file
    //

    newLocation = QDir(dirName);
    if (!newLocation.cd("0")) {
        newLocation.mkdir("0");
        newLocation.cd("0");
    }
    if (!newLocation.cd("uniform")) {
        newLocation.mkdir("uniform");
        newLocation.cd("uniform");
    }

    QString newFile  = newLocation.absoluteFilePath("generalizedMotionState");
    QString origFile = newFile + ".orig";

    if (QFile(origFile).exists()) {
        qWarning() << "overwriting " << origFile;
        QFile::remove(origFile);
    }
    QFile::rename(newFile, origFile);

    qDebug() << "move" << newFile << origFile;

    // update generalizedMotionState file
    this->exportgeneralizedMotionStateFile(origFile, newFile);

    //
    // ... fvSolution file
    //

    newLocation = QDir(dirName);
    if (!newLocation.cd("system")) {
        newLocation.mkdir("system");
        newLocation.cd("system");
    }

    // . use existing file, if exists, or use the template, if we are missing one ....

    // . parse solver section for keywords U|p|k|epsilon
    // .. add respective sections if missing.  Use U section, if exists, for missing sections

    // . look for solver definition for PISO && SIMPLE && PIMPLE;
    // .. add, if none found

    newFile = newLocation.absoluteFilePath("fvSolution");
    origFile = newFile + ".orig";

    if (QFile(newFile).exists()) {
        qWarning() << "using the provided " << newFile;
    }
    else {
        qWarning() << "creating a new " << newFile;

        if (QFile(origFile).exists()) {
            qWarning() << "overwriting " << origFile;
            QFile::remove(origFile);
        }
        QFile::rename(newFile, origFile);

        qDebug() << "move" << newFile << origFile;

        // write the new file
        QString solverType = solverComboBox->currentText();

        // load template file
        QFile tpl(":/Resources/CWE/Templates/fvSolution");
        tpl.open(QIODevice::ReadOnly);
        TemplateContents = tpl.readAll();
        tpl.close();

        QFile fvSol(newFile);
        fvSol.open(QFile::WriteOnly);
        QTextStream fvOut(&fvSol);

        QList<QByteArray> TemplateList = TemplateContents.split('\n');
        foreach (QByteArray line, TemplateList)
        {
            if (line.contains("__SOLVER__")) {

                // substitute __SOLVER__ section

                if (solverType.toLower() == "pimplefoam") {

                    fvOut << "PIMPLE" << ENDLN;
                    fvOut << "{" << ENDLN;
                    fvOut << "    //- Correct mesh flux option (default to true)" << ENDLN;
                    fvOut << "    correctPhi          true;" << ENDLN << ENDLN;

                    fvOut << "    //- Update mesh every outer correction loop (default to true)" << ENDLN;
                    fvOut << "    moveMeshOuterCorrectors true;" << ENDLN << ENDLN;
                    fvOut << "    //- Number of outer correction loops (an integer larger than 0 and default to 1)" << ENDLN;
                    fvOut << "    nOuterCorrectors    1;" << ENDLN << ENDLN;
                    fvOut << "    //- Number of PISO correction loops (an integer larger than 0 and default to 1)" << ENDLN;
                    fvOut << "    nCorrectors         1;" << ENDLN << ENDLN;
                    fvOut << "    //- Number of non-orthogonal correction loops (an integer no less than 0 and default to 0)" << ENDLN;
                    fvOut << "    nNonOrthogonalCorrectors 0;" << ENDLN;
                    fvOut << "}" << ENDLN;
                }
                else if (solverType.toLower() == "pisofoam") {

                    fvOut << "PISO" << ENDLN;
                    fvOut << "{" << ENDLN;
                    fvOut << "    pRefCell            0;" << ENDLN;
                    fvOut << "    pRefValue           0;" << ENDLN;
                    fvOut << "    nCorrectors         0;" << ENDLN;
                    fvOut << "    nNonOrthogonalCorrectors 0;" << ENDLN;
                    fvOut << "}" << ENDLN;
                }
                else if (solverType.toLower() == "icofoam") {

                    fvOut << "SIMPLE" << ENDLN;
                    fvOut << "{" << ENDLN;
                    fvOut << "    nNonOrthogonalCorrectors 0;" << ENDLN;
                    fvOut << "}" << ENDLN;
                }
            }
            else {
                fvOut << line << ENDLN;
            }
        }

        fvSol.close();
    }

    //
    // ... inflowProperties file
    //

    newLocation = QDir(dirName);
    if (!newLocation.cd("constant")) {
        newLocation.mkdir("constant");
        newLocation.cd("constant");
    }

    newFile = newLocation.absoluteFilePath("inflowProperties");
    origFile = newFile + ".orig";

    if (QFile(origFile).exists()) {
        qWarning() << "overwriting " << origFile;
        QFile::remove(origFile);
    }
    QFile::rename(newFile, origFile);

    qDebug() << "move" << newFile << origFile;

    // write the new file
    if (inflowCheckBox->isChecked() )
    {
        inflowWidget->exportInflowParameterFile(newFile);
    }

    //
    // ... U file
    //

    newLocation = QDir(dirName);
    if (!newLocation.cd("0")) {
        newLocation.mkdir("0");
        newLocation.cd("0");
    }

    newFile  = newLocation.absoluteFilePath("U");
    origFile = newFile + ".orig";

    if (QFile(origFile).exists()) {
        qWarning() << "overwriting " << origFile;
        QFile::remove(origFile);
    }
    QFile::rename(newFile, origFile);

    qDebug() << "move" << newFile << origFile;

    // update U file

    if (inflowCheckBox->isChecked() && !couplingGroup->isChecked()) {
        inflowWidget->exportUFile(newFile);
    } else {
        this->exportUFile(newFile);
    }

    //
    // ... controlDict file
    //

    newLocation = QDir(dirName);
    if (!newLocation.cd("system")) {
        newLocation.mkdir("system");
        newLocation.cd("system");
    }

    newFile  = newLocation.absoluteFilePath("controlDict");
    origFile = newFile + ".orig";

    if (QFile(origFile).exists()) {
        qWarning() << "overwriting " << origFile;
        QFile::remove(origFile);
    }
    QFile::rename(newFile, origFile);

    qDebug() << "move" << newFile << origFile;

    // update controlDict file
    this->exportControlDictFile(origFile, newFile);

    return true;
}

bool CFDExpertWidget::supportsLocalRun()
{
    return false;
}

void CFDExpertWidget::selectButtonPushed()
{
    if(remoteService->isLoggedIn())
    {
        RemoteCaseSelector selector(remoteService, this);
        selector.setWindowModality(Qt::ApplicationModal);
        selector.exec();
        if(selector.result() == QDialog::DialogCode::Accepted)
        {
            caseEditBox->setText(selector.getSelectedCase());
            this->downloadRemoteCaseFiles();
        }
        selector.close();
    } else {
        errorMessage("You need to Login Before you can Browse (Login button top right)");
    }
}

void CFDExpertWidget::selectPatchesPushed()
{
    if(remoteService->isLoggedIn())
    {
        PatchesSelector selector(patchesList, patchesEditBox->text(), this);
        selector.setWindowModality(Qt::ApplicationModal);
        if(selector.exec() == QDialog::DialogCode::Accepted)
            patchesEditBox->setText(selector.getPatches());
        selector.close();
    }
}

void CFDExpertWidget::downloadRemoteCaseFiles()
{
    if(remoteService->isLoggedIn())
    {
        QStringList remoteFilePath;
        remoteFilePath << getRemoteFilesPaths();

        QStringList localFilePath;
        localFilePath << originalUFilePath << originalControlDictPath;
        ensureUFileExists();
        remoteService->downloadFilesCall(remoteFilePath, localFilePath, this);

        this->readUfile(originalUFilePath);
        this->processUfile();
    }
}

void CFDExpertWidget::ensureUFileExists()
{
    QFile uFile(originalUFilePath);
    if (uFile.exists())
        return;

    QFileInfo fileInfo(originalUFilePath);
    QString dirPath = fileInfo.dir().absolutePath();
    QDir uFileDir(dirPath);
    if (!uFileDir.exists())
        uFileDir.mkpath(dirPath);

    uFile.open(QFile::ReadWrite);
    uFile.close();
}

QStringList CFDExpertWidget::getRemoteFilesPaths()
{
    QString caseDir = caseEditBox->text();

    if(caseDir.startsWith("agave://", Qt::CaseInsensitive))
    {
        caseDir = caseDir.remove(0, 8);
        caseDir = caseDir.prepend("system/");
    }

    return {caseDir + "/0/U", caseDir + "/system/controlDict"};
}

void CFDExpertWidget::resizeEvent(QResizeEvent *event)
{
    QSize theSize = event->size();
    scrollArea->setFixedSize(theSize);
    container->setFixedSize(container->minimumSizeHint());
}

void CFDExpertWidget::initializeUI()
{
    // put everything into a QScrollArea to accommodate the large inflow widget
    //
    // ... this also requires overloading the void resizeEvent(QResizeEvent *event) method !!!

    QVBoxLayout lyt(this);

    container = new QFrame();
    container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    scrollArea = new QScrollArea(this);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(container);
    lyt.addWidget(scrollArea);

    // here the actual contents

    auto layout = new QGridLayout(container);
    //layout->setMargin(0);
    layout->setSpacing(6);

    loginRequiredLabel = new QLabel(tr("Logging into DesignSafe is required to use CFD - Expert.\n"));
    layout->addWidget(loginRequiredLabel, 0, 0);

    QGroupBox* CFDGroupBox = new QGroupBox("OpenFOAM Parameters", this);

    QGridLayout *parametersLayout = new QGridLayout(CFDGroupBox);
    //parametersLayout->setMargin(6);
    parametersLayout->setSpacing(6);
    int row = 0;

    //QFormLayout* parametersLayout = new QFormLayout();

    caseEditBox = new QLineEdit(this);
    caseEditBox->setText("agave://designsafe.storage.community/SimCenter/Software/WE_UQ/Examples/SampleBuilding");
    caseEditBox->setToolTip(tr("OpenFOAM Remote Case Directory"));
    caseSelectButton = new QPushButton(tr("Browse"));
    caseEditBox->setMinimumWidth(400);

    QLabel *caseLabel = new QLabel("Case", this);
    parametersLayout->addWidget(caseLabel, row, 0);
    parametersLayout->addWidget(caseEditBox, row, 1);
    parametersLayout->addWidget(caseSelectButton, row, 2);

    //parametersLayout->addRow("Case", caseLayout);

    QHBoxLayout *hlyt = new QHBoxLayout();
    parametersLayout->addLayout(hlyt, ++row, 0, 1, 3);
    //
    lengthScale   = new QDoubleSpinBox(this);
    lengthScale->setValue(1.0);
    lengthScale->setMinimum(0.0);
    lengthScale->setMaximum(100.0);
    lengthScale->setDecimals(4);
    //
    velocityScale = new QDoubleSpinBox(this);
    velocityScale->setValue(1.0);
    velocityScale->setMinimum(0.0);
    velocityScale->setMaximum(100.0);
    velocityScale->setDecimals(4);
    //
    hlyt->addWidget(new QLabel("Length scale factor:"));
    hlyt->addWidget(lengthScale);
    QLabel *label = new QLabel("Velocity scale factor:");
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hlyt->addWidget(label);
    hlyt->addWidget(velocityScale);


    solverComboBox = new QComboBox(this);
    solverComboBox->addItem("pisoFoam");
    solverComboBox->addItem("icoFoam");
    solverComboBox->addItem("pimpleFoam");
    QLabel *solverLabel = new QLabel("Solver", this);
   // parametersLayout->addRow("Solver", solverComboBox);
    parametersLayout->addWidget(solverLabel, ++row, 0);
    parametersLayout->addWidget(solverComboBox, row, 1, 1, 2);
    solverComboBox->setToolTip(tr("OpenFOAM solver used in the analysis"));

    //Meshing
    meshingComboBox = new QComboBox(this);
    meshingComboBox->addItem("Mesh generation using blockMesh", "blockMesh");
    meshingComboBox->addItem("Mesh generation using snappyHexMesh", "snappyHexMesh");
    meshingComboBox->addItem("User provided mesh", "User");
    QLabel *meshingLabel = new QLabel("Meshing");
    //parametersLayout->addRow("Meshing", meshingComboBox);
    parametersLayout->addWidget(meshingComboBox, ++row, 1, 1, 2);
    parametersLayout->addWidget(meshingLabel, row, 0);
    meshingComboBox->setToolTip(tr("Method used for generating the mesh for the model"));

    //Force Calculation
    QLabel *forceLabel = new QLabel("Force Calculation", this);
    forceComboBox = new QComboBox();
    forceComboBox->addItem("Binning with uniform floor heights");
    //parametersLayout->addRow("Force Calculation     ", forceComboBox);
    parametersLayout->addWidget(forceComboBox, ++row, 1, 1, 2);
    parametersLayout->addWidget(forceLabel, row, 0);
    forceComboBox->setToolTip(tr("Method used for calculating the forces on the building model"));

    //Patches for building forces
    QLabel *patchesLabel = new QLabel("Building Patches", this);
    patchesEditBox = new QLineEdit("building");
    //patchesEditBox->setDisabled(true);
    patchesEditBox->setToolTip(tr("Patches used to extract the forces on the building model"));
    selectPatchesButton = new QPushButton("Select");
    parametersLayout->addWidget(patchesLabel, ++row, 0);
    parametersLayout->addWidget(patchesEditBox, row, 1);
    parametersLayout->addWidget(selectPatchesButton, row, 2);


    //Force Start Time
    QLabel *startTimeLabel = new QLabel("Start time", this);
    parametersLayout->addWidget(startTimeLabel, ++row, 0);
    startTimeBox = new QDoubleSpinBox(this);
    parametersLayout->addWidget(startTimeBox, row, 1, 1, 2);
    startTimeBox->setDecimals(3);
    startTimeBox->setSingleStep(0.001);
    startTimeBox->setMinimum(0);
    startTimeBox->setValue(0.01);
    startTimeBox->setToolTip(tr("The time in the OpenFOAM simulation when the building force event starts. Forces before that time are ignored."));

    //Number of processors
    QLabel *processorsLabel = new QLabel("Processors", this);
    parametersLayout->addWidget(processorsLabel, ++row, 0);
    processorsBox = new QSpinBox(this);
    parametersLayout->addWidget(processorsBox, row, 1, 1, 2);
    processorsBox->setMinimum(1);
    processorsBox->setMaximum(1024);
    processorsBox->setValue(16);
    processorsBox->setToolTip(tr("Number of processors used to run OpenFOAM in parallel."));

    // inflow parameters?
    inflowCheckBox = new QCheckBox();
    //parametersLayout->addRow("Inflow conditions", inflowCheckBox);
    QLabel *inflowLabel = new QLabel("Inflow Conditions     ");
    parametersLayout->addWidget(inflowCheckBox, ++row, 1);
    parametersLayout->addWidget(inflowLabel, row, 0);
    inflowCheckBox->setToolTip(tr("Indicate whether or not to include inflow condition specification"));


    // refresh button for reloading remote files
    refreshButton = new QPushButton("reload remote OpenFOAM files (takes a few seconds)");

    // use building coupling?
    couplingGroup = new UserModeShapes();

    //inflowWidget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);

    layout->addWidget(CFDGroupBox, 1, 0);
    //layout->addItem(new QSpacerItem(500,0,QSizePolicy::Expanding,QSizePolicy::Minimum), 1,1);
    layout->addWidget(refreshButton, 2,0);
    layout->addWidget(couplingGroup, 3,0);
    layout->addWidget(inflowWidget, 4,0);

    inflowWidget->setHidden(true);

    layout->setColumnStretch(0, 2);
    layout->setRowStretch(1, 0);
    layout->setRowStretch(2, 1);

    this->setEnabled(remoteService->isLoggedIn());
}

void CFDExpertWidget::setupConnections()
{
    connect(caseSelectButton, &QPushButton::clicked, this, &CFDExpertWidget::selectButtonPushed);

    connect(inflowCheckBox, &QCheckBox::stateChanged, this, [this](int state)
    {
        if(state)
        {
            inflowWidget->setHidden(false);
            downloadRemoteCaseFiles();
        }
        else
            inflowWidget->setHidden(true);

        container->setFixedSize(container->minimumSizeHint());
    });

    connect(inflowWidget, &InflowParameterWidget::rescaleRequested, this, [this](){
        container->setFixedSize(container->minimumSizeHint());
    });

    connect(remoteService, &RemoteService::downloadFilesReturn, this, [this](bool result, QObject* sender)
    {
        if(result && sender == this)
        {
            this->parseBoundaryPatches(originalUFilePath);

            // tell Widgets the latest about patch list ...
            inflowWidget->on_RemoteFilesChanged(originalUFilePath, originalControlDictPath);
            couplingGroup->updateBoundaryList(patchesList);

            this->processBuildingPatches();
        }
    });


    connect(inflowWidget, &InflowParameterWidget::uFileUpdateRequested, this, &CFDExpertWidget::downloadRemoteCaseFiles);

    connect(remoteService, &RemoteService::loginReturn, this, [this](bool loggedIn)
    {
        if(loggedIn && shown)
        {
	  loginRequiredLabel->hide();
	  this->setEnabled(true);
	  this->downloadRemoteCaseFiles();
        }
    });

    connect(remoteService, &RemoteService::logoutReturn, this, [this](bool loggedOut)
    {
        if (loggedOut)
        {
            loginRequiredLabel->show();
            this->setDisabled(true);
        }
    });

    connect(selectPatchesButton, &QPushButton::clicked, this, &CFDExpertWidget::selectPatchesPushed);

    connect(couplingGroup, SIGNAL(couplingGroup_checked(bool)), this, SLOT(on_couplingGroup_checked(bool)));

}

void CFDExpertWidget::parseBoundaryPatches(QString uFilePath)
{
    patchesList.clear();
    QFile uFile(uFilePath);

    if (!uFile.open(QFile::OpenModeFlag::ReadOnly))
        return;

    //We need to parse the U file;
    QTextStream uFileStream(&uFile);
    QString previousLine = "";
    QString line = "";

    while(previousLine != "boundaryField" && !uFileStream.atEnd())
    {
        previousLine = line;
        line = uFileStream.readLine().simplified();
    }

    while (!uFileStream.atEnd())
    {
        if (line == "}")
            break;

        previousLine = line;
        line = uFileStream.readLine().simplified();


        if(line == "{")
        {
            patchesList << previousLine;
            while(previousLine != "}" && !uFileStream.atEnd())
            {
                previousLine = line;
                line = uFileStream.readLine().simplified();
            }
        }
    }

    uFile.close();
}

void CFDExpertWidget::processBuildingPatches()
{
    if(!validateSelectedPatches())
        autoSelectPatches();
}

bool CFDExpertWidget::validateSelectedPatches()
{
    for(auto patch: patchesEditBox->text().split(','))
        if(!patchesList.contains(patch))
            return false;

    return true;
}

void CFDExpertWidget::autoSelectPatches()
{
    QStringList selectedPatches;

    for (auto patch: patchesList)
    {
        if(patch.toLower().contains("building") ||
            patch.toLower().contains("bldg") ||
            patch.toLower().contains("floor") ||
            patch.toLower().contains("story") )
            selectedPatches << patch;
    }

    patchesEditBox->setText(selectedPatches.join(','));
}

void CFDExpertWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if (!shown)
        shown = true;
}

void CFDExpertWidget::on_couplingGroup_checked(bool checked)
{
    if (checked)
    {
        solverComboBox->setCurrentText(QString("pimpleFoam"));
        solverComboBox->setEnabled(false);
    }
    else
    {
        solverComboBox->setCurrentIndex(0);
        solverComboBox->setEnabled(true);
    }
}

/* *******************************************************************
 *     migrated from InflowWidget
 * *******************************************************************/

void CFDExpertWidget::exportUFile(QString fileName)
{
    QMap<QString, double> theParameters;

    inflowWidget->fetchParameterMap(theParameters);

    // get the inflow boundary condition to generate
    QString inflow_BCselected = inflowWidget->fetchBoundarySelection();

    // get the coupling boundary condition to generate
    QString FSI_BCselected = couplingGroup->fetchBoundarySelection();

    // file handle for the U file
    QFile UFile(fileName);
    UFile.open(QFile::WriteOnly);
    QTextStream out(&UFile);

    out << UFileHead;

    foreach (QString key, boundaries.keys())
    {
        out << "    " << key << ENDLN;
        out << "    {" << ENDLN;

        if (inflowCheckBox->isChecked() && key == inflow_BCselected)
        {
            QMap<QString, QString> theMap = *boundaries.value(key);

            switch (int(theParameters.value("FilterMethod"))) {
            case 0: /* digital filter */

                out << "        type               turbulentDFMInlet;" << ENDLN;
                switch (int(theParameters.value("filterType"))) {
                case 0:
                    out << "        filterType         gaussian;" << ENDLN;
                    break;
                case 1:
                    out << "        filterType         exponential;" << ENDLN;
                    break;
                default:
                    out << "        filterType         exponential;" << ENDLN;
                }
                out << "        filterFactor       " << theParameters.value("filterFactor") << ";" << ENDLN;
                out << "        gridFactor         " << theParameters.value("gridFactor") << ";" << ENDLN;

                out << "        perodicInY         " << (( theParameters.value("periodicY") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        perodicInZ         " << (( theParameters.value("periodicZ") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        cleanRestart       " << (( theParameters.value("cleanRestart") > 0.1 ) ? "true" : "false") << ";" << ENDLN;

                break;

            case 1:  /* synthetic eddy */

                out << "        type               turbulentSEMInlet;" << ENDLN;
                switch (int(theParameters.value("eddyType"))) {
                case 0:
                    out << "        eddyType        gaussian;" << ENDLN;
                    break;
                case 1:
                    out << "        eddyType        tent;" << ENDLN;
                    break;
                case 2:
                    out << "        eddyType        step;" << ENDLN;
                    break;
                default:
                    out << "        eddyType        gaussian;" << ENDLN;
                }
                out << "        density            " << theParameters.value("eddyDensity") << ";" << ENDLN;

                out << "        perodicInY         " << (( theParameters.value("periodicY") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        perodicInZ         " << (( theParameters.value("periodicZ") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        cleanRestart       " << (( theParameters.value("cleanRestart")>0.1 ) ? "true" : "false") << ";" << ENDLN;

                break;

            case 2:  /* divergence-free synthetic eddy */

                out << "        type               turbulentDFSEMInlet;" << ENDLN;
                out << "        density            " << theParameters.value("divergenceFreeEddyDensity") << ";" << ENDLN;

                out << "        perodicInY         " << (( theParameters.value("periodicY") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        perodicInZ         " << (( theParameters.value("periodicZ") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        cleanRestart       " << (( theParameters.value("cleanRestart")>0.1 ) ? "true" : "false") << ";" << ENDLN;

                break;

            case 3:  /* digital spot */

                out << "        type               turbulentATSMInlet;" << ENDLN;

                out << "        vortonType         type" << ((theParameters.value("turbulentSpotType") > 0.0) ? "R" : "L" ) << ";" << ENDLN;
                out << "        density            " << theParameters.value("divergenceFreeEddyDensity") << ";" << ENDLN;

                out << "        perodicInY         " << (( theParameters.value("periodicY") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        perodicInZ         " << (( theParameters.value("periodicZ") > 0.1 ) ? "true" : "false") << ";" << ENDLN;
                out << "        cleanRestart       " << (( theParameters.value("cleanRestart")>0.1 ) ? "true" : "false") << ";" << ENDLN;

                break;

            default:
                qWarning() << "unknown turbulent inflow boundary conditions";
            }

            if (theParameters.value("interpolateParameters") < 0.1)   // shall we enter parameters (y) or interpolate (n)?
            {
                out << "        calculateU         true;" << ENDLN;
                out << "        calculateL         true;" << ENDLN;
                out << "        calculateR         true;" << ENDLN;
            }


            if (theMap.contains("type"))         theMap.remove("type");
            if (theMap.contains("filterType"))   theMap.remove("filterType");
            if (theMap.contains("filterFactor")) theMap.remove("filterFactor");
            if (theMap.contains("gridFactor"))   theMap.remove("gridFactor");
            if (theMap.contains("density"))      theMap.remove("density");
            if (theMap.contains("eddyType"))     theMap.remove("eddyType");
            if (theMap.contains("vortonType"))   theMap.remove("vortonType");
            if (theMap.contains("periodicInY"))  theMap.remove("periodicInY");
            if (theMap.contains("periodicInZ"))  theMap.remove("periodicInZ");
            if (theMap.contains("cleanRestart")) theMap.remove("cleanRestart");

            foreach (QString s, theMap.keys() )
            {
                out << "        " << s << "    " << theMap.value(s) << ";" << ENDLN;
            }
        }
        else if (couplingGroup->isChecked() && key == FSI_BCselected) {
            out <<  "        type               movingWallVelocity;" << ENDLN;
            out <<  "        value              uniform (0 0 0);" << ENDLN;
        }
        else {
            foreach (QString s, (boundaries.value(key))->keys() )
            {
                out << "        " << s << "    " << (boundaries.value(key))->value(s) << ";" << ENDLN;
            }
        }
        out << "    }" << ENDLN;
        out << ENDLN;
    }

    out << UFileTail;

    UFile.close();
}

void CFDExpertWidget::exportControlDictFile(QString origFileName, QString fileName)
{
    bool has_force_function = false;
    bool inside_functions_block = false;

    // file handle for the controlDict file
    QFile CDictIn(origFileName);
    CDictIn.open(QFile::ReadOnly);
    CDictContents = CDictIn.readAll();
    CDictIn.close();

    QFile CDict(fileName);
    CDict.open(QFile::WriteOnly);
    QTextStream out(&CDict);

    // parsing the given file line by line ...

    QList<QByteArray> CDictList = CDictContents.split('\n');
    foreach (QByteArray line, CDictList)
    {
        //
        // looking for "application" keyword ...
        //
        if (line.contains("application")) {

            // ... add loading the  libturbulentInflow.so

            if (inflowCheckBox->isChecked()) {
                out << "libs" << ENDLN;
                out << "(" << ENDLN;
                out << "    \"libturbulentInflow.so\"" << ENDLN;
                out << ");" << ENDLN;
                out << ENDLN;
            }

            out << "application     " << solverComboBox->currentText() << ";" << ENDLN;
        }
        //
        // looking for the "functions" keyword
        //
        else if (line.contains("functions")) {
            inside_functions_block = true;
            out << line << ENDLN;
        }
        //
        // looking for buildingsForces function
        //
        else if ( inside_functions_block &&
                 ( line.contains("buildingsForces") || line.contains("forces") ) ) {
            has_force_function = true;
            out << line << ENDLN;
        }
        else {
            out << line << ENDLN;
        }
    }

    CDict.close();

    // test if FSI has been checked by the user
    bool do_FSI_checked = couplingGroup->isChecked();

    if (do_FSI_checked && !has_force_function) {
        // this will be a problem!!!
        errorMessage("buildingsForces function undefined in controlDict");
    }
}

void CFDExpertWidget::exportgeneralizedMotionStateFile(QString origFileName, QString fileName)
{
    // get number of mode shapes
    int numModes = couplingGroup->numModes();
    if (numModes <= 0) {
        numModes = 1;  // safety catch to prevent crash if no modes have been given
    }
    QVector<double> zeros(numModes, 0.0);

    // file handle for the generalizedMotionState file
    QFile MS(fileName);
    MS.open(QFile::WriteOnly);
    QTextStream out(&MS);

    out << "/*--------------------------------*- C++ -*----------------------------------*\\" << ENDLN;
    out << " =========                 |                                                   " << ENDLN;
    out << " \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox             " << ENDLN;
    out << "  \\    /   O peration     | Website:  https://openfoam.org                    " << ENDLN;
    out << "   \\  /    A nd           | Version:  7                                       " << ENDLN;
    out << "    \\/     M anipulation  |                                                   " << ENDLN;
    out << "\\*---------------------------------------------------------------------------*/" << ENDLN;
    out << "FoamFile " << ENDLN;
    out << "{" << ENDLN;
    out << "   version     2.0;                      " << ENDLN;
    out << "   format      ascii;                    " << ENDLN;
    out << "   class       dictionary;               " << ENDLN;
    out << "   object      generalizedMotionState;   " << ENDLN;
    out << "}" << ENDLN;
    out << "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //" << ENDLN;
    out << ENDLN;

    out << "// Generalized displacements (a list of scalars)" << ENDLN;
    out << "ubar            " << OpenFoamHelper(zeros) << ";" << ENDLN;
    out << ENDLN;

    out << "// Generalized velocities (a list of scalars)"    << ENDLN;
    out << "vbar            " << OpenFoamHelper(zeros) << ";" << ENDLN;
    out << ENDLN;

    out << "// Generalized accelerations (a list of scalars)" << ENDLN;
    out << "abar            " << OpenFoamHelper(zeros) << ";" << ENDLN;
    out << ENDLN;

    MS.close();
}

bool CFDExpertWidget::readUfile(QString filename)
{
    QFile UFile(filename);

    if (UFile.exists()) {
        //
        // U file exists
        //
        UFile.open(QFile::ReadOnly);
        UFileContents = UFile.readAll();
        UFile.close();

        return true;
    }
    else {
        //
        // U file missing
        //
        UFileContents = "";

        return false;
    }
}

bool CFDExpertWidget::readControlDict(QString filename)
{
    QFile CDictFile(filename);

    if (CDictFile.exists()) {
        //
        // controlDict file exists
        //
        CDictFile.open(QFile::ReadOnly);
        CDictContents = CDictFile.readAll();
        CDictFile.close();

        return true;
    }
    else {
        //
        // controlDict file missing
        //
        CDictContents = "";

        return false;
    }
}

bool CFDExpertWidget::getLine(QStringList &reply)
{
    bool hasLine = false;
    QByteArray lineString = "";

    while (UIter->hasNext() && (!hasLine))
    {
        QByteArray line = UIter->next().simplified();
        if (qstrncmp(line,"//",2) == 0) continue;
        if (qstrncmp(line, "#",1) == 0) continue;
        if (line.contains('{')) {
            hasLine = true;
            break;
        }
        lineString += line;
        if (line.contains('}')) {
            hasLine = true;
            break;
        }
        if (line.contains(';')) {
            int idx = lineString.indexOf(';');
            lineString.truncate(idx);
            hasLine = true;
            break;
        }
    }

    reply.clear();

    if (hasLine)
    {
        QByteArrayList reply0 = lineString.simplified().split(' ');

        foreach (QByteArray item, reply0)
        {
            reply.append(item);
        }
    }

    return hasLine;
}

QMap<QString, QString> *CFDExpertWidget::readParameters(void)
{
    QMap<QString, QString> *params = new QMap<QString, QString>();

    QStringList items;

    while ( this->getLine(items) ) {
        if (items[0] == '}') break;

        if (items.length() > 0 ) {
            QString key = items[0];
            items.removeFirst();
            QString value = items.join(" ");
            params->insert(key, value);
        }
    }

    return params;
}

void CFDExpertWidget::processUfile()
{
    // parse files for available boundaries
    QStringList boundaryList;
    UFileHead = "";
    UFileTail = "";

    UFileList = UFileContents.split('\n');
    UIter = new QListIterator<QByteArray>(UFileList);

    // read till boundaryField keyword
    while (UIter->hasNext())
    {
        QByteArray line = UIter->next();
        UFileHead.append(line);
        UFileHead.append('\n');
        if (line.contains("boundaryField")) {
            while ( (!line.contains('{')) && UIter->hasNext()) {
                line = UIter->next();
                UFileHead.append(line);
                UFileHead.append('\n');
            }
            break;
        }
    }

    // parse for boundary patches
    while (UIter->hasNext())
    {
        QStringList list;

        if (this->getLine(list))
        {
            // skip empty lines
            if (list.length() == 0) continue;

            // terminate if done with boundaryFields section
            if (list[0] == '}') {
                UFileTail.append("}\n");
                break;
            }

            // read and store the boundary item
            boundaryList.append(list[0]);
            boundaries.insert(list[0], this->readParameters());
        }
    }

    // collect the remainder of the file
    while (UIter->hasNext())
    {
        QByteArray line = UIter->next();
        UFileTail.append(line);
        UFileTail.append('\n');
    }

    couplingGroup->updateBoundaryList(boundaryList);
}
