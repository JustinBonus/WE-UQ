#ifndef WIND_EVENT_SELECTION_H
#define WIND_EVENT_SELECTION_H

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

// Written: fmckenna

#include <SimCenterAppWidget.h>

#include <QGroupBox>
#include <QVector>
#include <ExpertCFD/CFDExpertWidget.h>
#include <ExpertCFD/UI/CFDTemplateWidget.h>
#include <RemoteService.h>

class QComboBox;
class QStackedWidget;
class UserDefinedApplication;

class RandomVariablesContainer;

class WindEventSelection : public  SimCenterAppWidget
{
    Q_OBJECT
public:
    explicit WindEventSelection(RandomVariablesContainer *, RemoteService* remoteService, QWidget *parent = 0);
    ~WindEventSelection();

    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool outputAppDataToJSON(QJsonObject &jsonObject);
    bool inputAppDataFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &destName);
    bool supportsLocalRun() override;
    SimCenterAppWidget* getCurrentEvent();

signals:
    void statusMessage(QString message);
    void errorMessage(QString message);
    void fatalMessage(QString message);
    void typeEVT(QString type);

public slots:
   void eventSelectionChanged(const QString &arg1);
   void sendStatusMessage(QString message);
   void sendErrorMessage(QString message);
   void sendFatalMessage(QString message);
   void replyEventType(void);

private:
   QComboBox   *eventSelection;
   QStackedWidget *theStackedWidget;
   SimCenterAppWidget *theCurrentEvent;

   SimCenterAppWidget *theStochasticModel;
   SimCenterAppWidget *theIsolatedBuildingCFD;
   SimCenterAppWidget *theSurroundedBuildingCFD;
   SimCenterAppWidget *theDigitalWindTunnel;
   SimCenterAppWidget *theExperimentalWindForces;
   SimCenterAppWidget *theExperimentalWindPressures;
   SimCenterAppWidget *theWindForceSpectrum;
   SimCenterAppWidget *theDEDM_HRP_Widget;
   SimCenterAppWidget *theLowRiseTPU_Widget;
   SimCenterAppWidget *theHighRiseTPU_Widget;  
   SimCenterAppWidget *theWindTunnelExperiment;
   SimCenterAppWidget *theExistingEvents;

   RandomVariablesContainer *theRandomVariablesContainer;
};

#endif // WIND_EVENT_SELECTION_H
