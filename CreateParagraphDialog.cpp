/*****************************************************************************
 * FILE NAME    : CreateParagraphDialog.cpp
 * DATE         : February 04 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QComboBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CreateParagraphDialog.h"

/*****************************************************************************!
 * Function : CreateParagraphDialog
 *****************************************************************************/
CreateParagraphDialog::CreateParagraphDialog
() : QDialog()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~CreateParagraphDialog
 *****************************************************************************/
CreateParagraphDialog::~CreateParagraphDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
CreateParagraphDialog::Initialize(void)
{
  CreateSubWindows();  
  CreateConnections();
  resize(CREATE_PARAGRAPH_DIALOG_WIDTH, CREATE_PARAGRAPH_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
CreateParagraphDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
CreateParagraphDialog::CreateSubWindows(void)
{
  QStringList                           indentItems;
  int                                   verticalGap;
  int                                   labelX;
  int                                   labelY;
  int                                   labelWidth;
  int                                   labelHeight;
  QFont                                 labelFont;

  int                                   comboX;
  int                                   comboHeight;
  int                                   comboWidth;
  
  QLabel*                               label;
  
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
  okButtonX = CREATE_PARAGRAPH_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (2 * buttonGap));
  cancelButtonX = CREATE_PARAGRAPH_DIALOG_WIDTH - (cancelButtonWidth + buttonGap);
  buttonY = CREATE_PARAGRAPH_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
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

  header = new WindowHeader("Paragraph Configure", this);
  header->SetFontSize(12);
  header->SetBackgroundColor(QColor("#CCCCCC"));
  header->move(0, 0);
  header->resize(100, WINDOW_HEADER_HEIGHT);
  
  //! 
  labelX = 0;
  labelY = WINDOW_HEADER_HEIGHT + 10;
  labelWidth = 100;
  labelHeight = 20;
  comboX = 110;
  comboWidth = 100;
  comboHeight = 20;
  verticalGap = 10;
  labelFont = QFont("Segoe UI", 10, QFont::Normal);
  
  //! 
  label = new QLabel("Left Indent :", this);
  label->move(labelX, labelY);
  label->setAlignment(Qt::AlignRight);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);

  indentItems << "0" << "25" << "50" << "75" << "100";
  
  LeftIndentCombo = new QComboBox(this);
  LeftIndentCombo->move(comboX, labelY);
  LeftIndentCombo->resize(comboWidth, comboHeight);
  LeftIndentCombo->addItems(indentItems);
  LeftIndentCombo->setCurrentIndex(1);
  labelY += labelHeight + verticalGap;
  
  //! 
  label = new QLabel("Right Indent :", this);
  label->move(labelX, labelY);
  label->setAlignment(Qt::AlignRight);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);

  RightIndentCombo = new QComboBox(this);
  RightIndentCombo->move(comboX, labelY);
  RightIndentCombo->resize(comboWidth, comboHeight);
  RightIndentCombo->addItems(indentItems);
  RightIndentCombo->setCurrentIndex(1);
  labelY += labelHeight + verticalGap;
  
  label = new QLabel("Top Indent :", this);
  label->move(labelX, labelY);
  label->setAlignment(Qt::AlignRight);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);
  TopIndentCombo = new QComboBox(this);
  TopIndentCombo->move(comboX, labelY);
  TopIndentCombo->resize(comboWidth, comboHeight);
  TopIndentCombo->addItems(indentItems);
  TopIndentCombo->setCurrentIndex(1);
  labelY += labelHeight + verticalGap;
  
  label = new QLabel("Bottom Indent :", this);
  label->move(labelX, labelY);
  label->setAlignment(Qt::AlignRight);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);
  BottomIndentCombo = new QComboBox(this);
  BottomIndentCombo->move(comboX, labelY);
  BottomIndentCombo->resize(comboWidth, comboHeight);
  BottomIndentCombo->addItems(indentItems);
  BottomIndentCombo->setCurrentIndex(1);
  labelY += labelHeight + verticalGap;
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
CreateParagraphDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
CreateParagraphDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
CreateParagraphDialog::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   CancelButtonW;
  int                                   CancelButtonH;
  int                                   CancelButtonY;
  int                                   CancelButtonX;
  int                                   OKButtonW;
  int                                   OKButtonH;
  int                                   OKButtonY;
  int                                   OKButtonX;
  int                                   headerW;
  int                                   headerH;
  int                                   headerY;
  int                                   headerX;
  int                                   buttonGap;
  
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  buttonGap = 5;
  
  //! 
  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = header->size().height();

  //! 
  CancelButtonW = CancelButton->size().width();
  CancelButtonH = CancelButton->size().height();
  CancelButtonX = (width - (CancelButtonW + buttonGap));
  CancelButtonY = (height - (CancelButtonH + buttonGap));

  //! 
  OKButtonW = OKButton->size().width();
  OKButtonH = OKButton->size().height();
  OKButtonX = width - (CancelButtonW + OKButtonW + buttonGap * 2);
  OKButtonY = height - ( OKButtonH + buttonGap);

  //! 
  OKButton->move(OKButtonX, OKButtonY);
  OKButton->resize(OKButtonW, OKButtonH);

  CancelButton->move(CancelButtonX, CancelButtonY);
  CancelButton->resize(CancelButtonW, CancelButtonH);

  header->move(headerX, headerY);
  header->resize(headerW, headerH);
}

/*****************************************************************************!
 * Function : GetLeftIndent
 *****************************************************************************/
int
CreateParagraphDialog::GetLeftIndent
()
{
  QString                               st;
  st = LeftIndentCombo->currentText();
  return st.toInt();
}

/*****************************************************************************!
 * Function : GetRightIndent
 *****************************************************************************/
int
CreateParagraphDialog::GetRightIndent
()
{
  QString                               st;
  st = RightIndentCombo->currentText();
  return st.toInt();
}

/*****************************************************************************!
 * Function : GetTopIndent
 *****************************************************************************/
int
CreateParagraphDialog::GetTopIndent
()
{
  QString                               st;
  st = TopIndentCombo->currentText();
  return st.toInt();
}

/*****************************************************************************!
 * Function : GetBottomIndent
 *****************************************************************************/
int
CreateParagraphDialog::GetBottomIndent
()
{
  QString                               st;
  st = BottomIndentCombo->currentText();
  return st.toInt();  
}

