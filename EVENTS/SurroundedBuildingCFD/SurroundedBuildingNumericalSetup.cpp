/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written by: Abiy

#include "SurroundedBuildingCFD.h"
#include "SurroundedBuildingNumericalSetup.h"
#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <SectionTitle.h>
#include <QFileInfo>
#include <QMovie>
#include <QPixmap>
#include <QIcon>
#include <RandomVariablesContainer.h>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QVector>
#include <LineEditRV.h>
#include <QProcess>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <SimCenterPreferences.h>
#include <GeneralInformationWidget.h>

SurroundedBuildingNumericalSetup::SurroundedBuildingNumericalSetup(SurroundedBuildingCFD *parent)
    : SimCenterAppWidget(parent), mainModel(parent)
{
    layout = new QVBoxLayout();

    parallelizationGroup = new QGroupBox("Parallelization", this);
    parallelizationLayout = new QGridLayout();
    parallelizationGroup->setLayout(parallelizationLayout);

    solverSelectionGroup = new QGroupBox("Solver Selection", this);
    solverSelectionLayout = new QGridLayout();
    solverSelectionGroup->setLayout(solverSelectionLayout);

    durationAndTimeStepGroup = new QGroupBox("Duration and Timestep", this);
    durationAndTimeStepLayout = new QGridLayout();
    durationAndTimeStepGroup->setLayout(durationAndTimeStepLayout);

    //==================================================================
    //              General Options
    //==================================================================
    QLabel* numProcessorsLabel = new QLabel("Number of Processors:");

    runInParallel = new QCheckBox("Run Simulation in Parallel");
    runInParallel->setChecked(true);
    runInParallel->setToolTip("Run the CFD simulation in parallel or not");

    numProcessors = new QSpinBox();
    numProcessors->setSingleStep(10);
    numProcessors->setMinimum(1);
    numProcessors->setMaximum(1024);
    numProcessors->setValue(56);
    numProcessors->setToolTip("Number of processors to run the simulation with");

    parallelizationLayout->addWidget(runInParallel, 0, 0);
    parallelizationLayout->addWidget(numProcessorsLabel, 0, 1, Qt::AlignRight);
    parallelizationLayout->addWidget(numProcessors, 0, 2);


    //==================================================================
    //              Solver selection
    //==================================================================
    solverTypeLabel = new QLabel("Solver Type:");
    numNonOrthogonalCorrectorsLabel = new QLabel("Number of Non-Orthogonal Correctors:");
    numOuterCorrectorsLabel = new QLabel("Number of Outer Corrector Loops:");
    numCorrectorsLabel = new QLabel("Number Corrector Loops:");

    numOuterCorrectorsLabel->setEnabled(false);
    numCorrectorsLabel->setEnabled(false);

    solverType = new QComboBox();

    solverType->addItem("pisoFoam");
    solverType->addItem("pimpleFoam");
    solverType->addItem("simpleFoam");

    solverType->setToolTip("Solver type (for LES use pisoFoam or pimpleFoam)");

    numNonOrthogonalCorrectors = new QSpinBox();
    numNonOrthogonalCorrectors->setSingleStep(1);
    numNonOrthogonalCorrectors->setMinimum(0);
    numNonOrthogonalCorrectors->setValue(1);
    numNonOrthogonalCorrectors->setToolTip("Number of non-orthogonal correction loops (should be at least 1 for non-orthogonal mesh)");

    numCorrectors = new QSpinBox();
    numCorrectors->setSingleStep(1);
    numCorrectors->setMinimum(1);
    numCorrectors->setValue(2);
    numCorrectors->setEnabled(false);
    numCorrectors->setToolTip("Number of pressure correction loops");

    numOuterCorrectors = new QSpinBox();
    numOuterCorrectors->setSingleStep(1);
    numOuterCorrectors->setMinimum(1);
    numOuterCorrectors->setValue(1);
    numOuterCorrectors->setEnabled(false);
    numOuterCorrectors->setToolTip("Number of outer correction loops (if 1 runs in PISO mode)");

    solverSelectionLayout->addWidget(solverTypeLabel, 0, 0);
    solverSelectionLayout->addWidget(numNonOrthogonalCorrectorsLabel, 1, 0);
    solverSelectionLayout->addWidget(numCorrectorsLabel, 2, 0);
    solverSelectionLayout->addWidget(numOuterCorrectorsLabel, 3, 0);

    solverSelectionLayout->addWidget(solverType, 0, 1);
    solverSelectionLayout->addWidget(numNonOrthogonalCorrectors, 1, 1);
    solverSelectionLayout->addWidget(numCorrectors, 2, 1);
    solverSelectionLayout->addWidget(numOuterCorrectors, 3, 1);

    //==================================================================
    //              Duration and time step controls
    //==================================================================
    durationLabel = new QLabel("Duration: ");
    timeStepLabel = new QLabel("Time Step: ");
    maxCourantNumberLabel = new QLabel("Maximum Courant Number: ");
    maxCourantNumberLabel->setEnabled(false);

    duration = new QLineEdit();
    duration->setText("10.0");
    duration->setToolTip("Duration or end time of the simulation");


    timeStep = new QLineEdit();
    timeStep->setText("0.0001");
    timeStep->setToolTip("Time step");

    constTimeStep = new QRadioButton("Constant");
    constTimeStep->setChecked(true);
    constTimeStep->setToolTip("Use constant time step for the solver");


    adjustTimeStep = new QRadioButton("Adjustable");
    adjustTimeStep->setChecked(false);
    adjustTimeStep->setToolTip("Use adjustable time step for the solver");

    maxCourantNumber = new QDoubleSpinBox();
    maxCourantNumber->setSingleStep(1);
    maxCourantNumber->setMinimum(0.5);
    maxCourantNumber->setValue(1);
    maxCourantNumber->setEnabled(false);
    maxCourantNumber->setToolTip("Maximum value of Courant number for adjustable time step");

    calculateTimeStep = new QPushButton("Calculate");


    durationAndTimeStepLayout->addWidget(durationLabel, 0, 0);
    durationAndTimeStepLayout->addWidget(duration, 0, 1);


    durationAndTimeStepLayout->addWidget(timeStepLabel, 1, 0);
    durationAndTimeStepLayout->addWidget(timeStep, 1, 1);


    durationAndTimeStepLayout->addWidget(calculateTimeStep, 1, 2);
    durationAndTimeStepLayout->addWidget(constTimeStep, 1, 3);
    durationAndTimeStepLayout->addWidget(adjustTimeStep, 1, 4);

    durationAndTimeStepLayout->addWidget(maxCourantNumberLabel, 2, 0);
    durationAndTimeStepLayout->addWidget(maxCourantNumber, 2, 1);

    layout->addWidget(solverSelectionGroup);
    layout->addWidget(durationAndTimeStepGroup);
    layout->addWidget(parallelizationGroup);

    this->setLayout(layout);


    //Add signals
    connect(runInParallel, SIGNAL(stateChanged(int)), this, SLOT(onRunInParallelChecked(int)));
    connect(solverType, SIGNAL(currentIndexChanged(QString)), this, SLOT(solverTypeChanged(QString)));
    connect(adjustTimeStep, SIGNAL(toggled(bool)), this, SLOT(timeStepOptionChanged(bool)));
    connect(calculateTimeStep, SIGNAL(clicked()), this, SLOT(onCalculateTimeStepClicked()));

}


SurroundedBuildingNumericalSetup::~SurroundedBuildingNumericalSetup()
{

}

void SurroundedBuildingNumericalSetup::clear(void)
{

}

void SurroundedBuildingNumericalSetup::updateWidgets(void)
{
    if(mainModel->simulationType() == "RANS")
    {
        solverType->setCurrentIndex(0);
        solverTypeChanged("simpleFoam");
    }
    else if (mainModel->simulationType() == "LES")
    {
        solverType->setCurrentIndex(1);
        solverTypeChanged("pisoFoam");
    }
    else if (mainModel->simulationType() == "DES")
    {
        solverType->setCurrentIndex(1);
        solverTypeChanged("pisoFoam");
    }
}

void SurroundedBuildingNumericalSetup::solverTypeChanged(const QString &arg1)
{
    if (arg1 == "simpleFoam")
    {
        numCorrectors->setEnabled(false);
        numCorrectorsLabel->setEnabled(false);

        numOuterCorrectors->setEnabled(false);
        numOuterCorrectorsLabel->setEnabled(false);
    }
    else if (arg1 == "pisoFoam")
    {
        numCorrectors->setEnabled(true);
        numCorrectorsLabel->setEnabled(true);

        numOuterCorrectors->setEnabled(false);
        numOuterCorrectorsLabel->setEnabled(false);
    }
    else if(arg1 == "pimpleFoam")
    {
        numCorrectors->setEnabled(true);
        numCorrectorsLabel  ->setEnabled(true);

        numOuterCorrectors->setEnabled(true);
        numOuterCorrectorsLabel->setEnabled(true);
    }
    else
    {
        qDebug() << "ERROR .. solver selection.. type unknown: " << arg1;
    }
}

void SurroundedBuildingNumericalSetup::timeStepOptionChanged(const bool arg1)
{
    if (adjustTimeStep->isChecked() && solverType->currentText()=="pimpleFoam")
    {
        maxCourantNumber->setEnabled(true);
        maxCourantNumberLabel->setEnabled(true);
    }
    else
    {
        maxCourantNumber->setEnabled(false);
        maxCourantNumberLabel->setEnabled(false);
        constTimeStep->setChecked(true);
    }
}

void SurroundedBuildingNumericalSetup::onRunInParallelChecked(int state)
{

    if (!runInParallel->isChecked())
    {
        numProcessors->setValue(1);
    }
    else
    {
        numProcessors->setValue(64);
    }

    numProcessors->setEnabled(runInParallel->isChecked()) ;
}

void SurroundedBuildingNumericalSetup::onCalculateTimeStepClicked()
{
    timeStep->setText(QString::number(mainModel->getTimeStep()));
}

bool SurroundedBuildingNumericalSetup::outputToJSON(QJsonObject &jsonObject)
{
    // Writes numerical setup to JSON file.

    QJsonObject numericalSetupJson = QJsonObject();

    numericalSetupJson["solverType"] = solverType->currentText();
    numericalSetupJson["numNonOrthogonalCorrectors"] = numNonOrthogonalCorrectors->value();
    numericalSetupJson["numCorrectors"] = numCorrectors->value();
    numericalSetupJson["numOuterCorrectors"] = numOuterCorrectors->value();
    numericalSetupJson["duration"] = duration->text().toDouble();
    numericalSetupJson["timeStep"] = timeStep->text().toDouble();
    numericalSetupJson["maxCourantNumber"] = maxCourantNumber->value();
    numericalSetupJson["adjustTimeStep"] = adjustTimeStep->isChecked();
    numericalSetupJson["runInParallel"] = runInParallel->isChecked();
    numericalSetupJson["numProcessors"] = numProcessors->value();

    jsonObject["numericalSetup"] = numericalSetupJson;

    return true;
}

bool SurroundedBuildingNumericalSetup::inputFromJSON(QJsonObject &jsonObject)
{
    // Input numerical setup information to JSON file.

    QJsonObject numericalSetupJson = jsonObject["numericalSetup"].toObject();

    solverType->setCurrentText(numericalSetupJson["solverType"].toString());
    numNonOrthogonalCorrectors->setValue(numericalSetupJson["numNonOrthogonalCorrectors"].toInt());
    numCorrectors->setValue(numericalSetupJson["numCorrectors"].toInt());
    numOuterCorrectors->setValue(numericalSetupJson["numOuterCorrectors"].toInt());
    duration->setText(QString::number(numericalSetupJson["duration"].toDouble()));
    timeStep->setText(QString::number(numericalSetupJson["timeStep"].toDouble()));
    maxCourantNumber->setValue(numericalSetupJson["maxCourantNumber"].toDouble());
    adjustTimeStep->setChecked(numericalSetupJson["adjustTimeStep"].toBool());
    runInParallel->setChecked(numericalSetupJson["runInParallel"].toBool());;
    numProcessors->setValue(numericalSetupJson["numProcessors"].toDouble());

    return true;
}

