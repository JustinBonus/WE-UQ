#ifndef _KWON_KAREEM_2006_H
#define _KWON_KAREEM_2006_H

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
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
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

// Written: mhgardner

#include <LineEditRV.h>
#include <QFormLayout>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QString>
#include <QWidget>
#include <RandomVariablesContainer.h>
#include <SimCenterWidget.h>
#include "StochasticModelWidget.h"

// Forward declarations
class LineEditRV;
class QFormLayout;
class QJsonObject;
class QLabel;
class QLineEdit;
class QRadioButton;
class QSpinBox;
class QString;
class QWidget;
class QComboBox;
class RandomVariablesContainer;

/**
 * Widget for inputting parameters for stochastic earthquake time history
 * generation model
 */
class KwonKareem2006 : public StochasticModelWidget {
  Q_OBJECT
 public:
  /**
   * @constructor Construct new stochastic model input widget
   * @param[in, out] random_variables Widget to store random variables to
   * @param[in, out] parent Pointer to parent widget. Defaults to nullptr.
   */
  explicit KwonKareem2006(RandomVariablesContainer* random_variables,
                            QWidget* parent = nullptr);

  /**
   * @destructor Virtual desctructor for stochastic model input widget
   */
  virtual ~KwonKareem2006() {};

  /**
   * Instantiate stochastic motion input widget from input JSON object
   * @param[in] rvObject JSON object containing input information
   * @return Returns true if successful, false otherwise
   */
  bool inputFromJSON(QJsonObject& rvObject) override;

  /**
   * Write all current class data to JSON required to reconstruct class
   * @param[in, out] rvObject JSON object to write output to
   * @return Returns true if successful, false otherwise
   */
  bool outputToJSON(QJsonObject& rvObject) override;

 public slots:
  /**
   * Update ability to provide seed based on changed status of radio button
   * @param[in] checked Current status of radio button for providing seed
   */
  void provideSeed(const bool& checked);

 protected:
  QLabel *modelDescription; /**< Brief description of model indicating relevant
				 paper where more information can be found describing
				 model in greater detail */

  QComboBox *exposureCategory; /**< ASCE 7 Exposure condition */
  LineEditRV *dragCoefficient; /**< drag Coefficient */
  LineEditRV *gustWindSpeed; /**< gust wnind speed (mph) */
  QSpinBox *seed; /**< Value to use as seed for motion generation */
  QRadioButton *useSeed; /**< Radio button to indicate whether specific seed
                              value should be used */
};

#endif  // _KWON_KAREEM_2006_MODEL_H
