/*********************************************************************************
**
** Copyright (c) 2018 The University of Notre Dame
** Copyright (c) 2018 The Regents of the University of California
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:

#include "sctrtextdatawidget.h"

SCtrTextDataWidget::SCtrTextDataWidget(QWidget *parent):
    SCtrMasterDataWidget(parent)
{

}

SCtrTextDataWidget::~SCtrTextDataWidget()
{
    if (theValue != nullptr) theValue->deleteLater();
    if (label_varName != nullptr) label_varName->deleteLater();
}

QString SCtrTextDataWidget::shownValue()
{
    return theValue->text();
}

void SCtrTextDataWidget::initUI()
{
    QBoxLayout *layout = new QHBoxLayout();
    //layout->setMargin(0);

    theValue = new QLineEdit(this);
    label_varName = new QLabel(getTypeInfo().displayName, this);

    layout->addWidget(label_varName, 3);
    layout->addWidget(theValue, 4);

    this->setLayout(layout);

    QObject::connect(theValue, SIGNAL(textChanged(QString)),
                     this, SLOT(changeMadeToUnderlyingDataWidget()));
}

void SCtrTextDataWidget::setComponetsEnabled(bool newSetting)
{
    theValue->setEnabled(newSetting);
}

void SCtrTextDataWidget::setShownValue(QString newValue)
{
    theValue->setText(newValue);
}
