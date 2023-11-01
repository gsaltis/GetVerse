/*****************************************************************************
 * FILE NAME    : InterlinearDisplayElementSelectDialog.cpp
 * DATE         : October 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearDisplayElementSelectDialog.h"

/*****************************************************************************!
 * Function : InterlinearDisplayElementSelectDialog
 *****************************************************************************/
InterlinearDisplayElementSelectDialog::InterlinearDisplayElementSelectDialog
() : QDialog()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~InterlinearDisplayElementSelectDialog
 *****************************************************************************/
InterlinearDisplayElementSelectDialog::~InterlinearDisplayElementSelectDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
InterlinearDisplayElementSelectDialog::Initialize(void)
{
  CreateSubWindows();  
  CreateConnections();
  resize(INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_WIDTH, INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
InterlinearDisplayElementSelectDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
InterlinearDisplayElementSelectDialog::CreateSubWindows(void)
{
  int                                   buttonHeight;
  int                                   buttonGap;
  int                                   cancelButtonX;
  int                                   okButtonX;
  int                                   buttonY;
  int                                   cancelButtonWidth;
  int                                   okButtonWidth;
  
  okButtonWidth = 40;
  cancelButtonWidth = 60;
  buttonGap = 5;
  buttonHeight = 20;
  okButtonX = INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (2 * buttonGap));
  cancelButtonX = INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_WIDTH - (cancelButtonWidth + buttonGap);
  buttonY = INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
  OKButton = new QPushButton();
  OKButton->setParent(this);
  OKButton->setText("OK");
  OKButton->move(okButtonX, buttonY);
  OKButton->resize(okButtonWidth, buttonHeight);
  
  CancelButton = new QPushButton();
  CancelButton->setParent(this);
  CancelButton->setText("Cancel");
  CancelButton->move(cancelButtonX, buttonY);
  CancelButton->resize(cancelButtonWidth, buttonHeight);
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
InterlinearDisplayElementSelectDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
InterlinearDisplayElementSelectDialog::SlotCancelButtonPressed()
{
  reject();
}
