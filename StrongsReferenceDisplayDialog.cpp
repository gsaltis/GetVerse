/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayDialog.cpp
 * DATE         : November 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <sqlite3.h>
#include <unistd.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayDialog.h"
#include "Common.h"

/*****************************************************************************!
 * Function : StrongsReferenceDisplayDialog
 *****************************************************************************/
StrongsReferenceDisplayDialog::StrongsReferenceDisplayDialog
(InterlinearWord* InWord) : QDialog()
{
  interlinearWord = InWord;
  Initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceDisplayDialog
 *****************************************************************************/
StrongsReferenceDisplayDialog::~StrongsReferenceDisplayDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::Initialize(void)
{
  ReadStrongsDatabase();
  GradientColorLight = QColor(205, 205, 205);
  GradientColorDark = QColor(114, 114, 114);

  LabelFont = QFont("Segoe UI", 10, QFont::Bold);
  HeaderFont = QFont("Segoe UI", 13, QFont::Bold);
  DataFont = QFont("Segoe UI", 10, QFont::Normal);
  ContextualFont = QFont("Times New Roman", 14, QFont::Normal);
  resize(STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH, STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT);
  CreateSubWindows();  
  CreateConnections();
  resize(STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH, STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::CreateSubWindows(void)
{
  int                                   buttonHeight;
  int                                   buttonGap;
  int                                   okButtonX;
  int                                   buttonY;
  int                                   okButtonWidth;
  
  okButtonWidth = 40;
  buttonGap = 5;
  buttonHeight = 20;
  okButtonX = STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH - (okButtonWidth + buttonGap);
  buttonY = STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
  OKButton = new QPushButton();
  OKButton->setParent(this);
  OKButton->setText("OK");
  OKButton->move(okButtonX, buttonY);
  OKButton->resize(okButtonWidth, buttonHeight);

  CreateHeaderBlock();
  CreateLabelBlock();
  CreateDataBlock();
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::SlotOKButtonPressed()
{
  TRACE_FUNCTION_LOCATION();
  accept();
}

/*****************************************************************************!
 * Function : ReadStrongsDatabase
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::ReadStrongsDatabase(void)
{
  int                                   retryTimes;
  QString                               selectStatement;
  sqlite3_stmt*                         statement;
  int                                   n;
  bool                                  finished;

  selectStatement = QString("SELECT "
                            "ID, "                                      // 0
                            "LEXICAL_FORM, "                            // 1
                            "TRANSLITERATED_LEXICAL_FORM, "             // 2
                            "PART_OF_SPEECH, "                          // 3
                            "PHONETIC_SPELLING, "                       // 4
                            "DEFINITION, "                              // 5
                            "ORIGIN, "                                  // 6
                            "USAGE "                                    // 7
                            "FROM STRONGS_WORD WHERE ID is \"%1\";").
    arg(interlinearWord->GetStrongsWordID());
  n = sqlite3_prepare_v2(MainInterlinearDatabase,
                         selectStatement.toStdString().c_str(),
                         selectStatement.length(),
                         &statement,
                         NULL);
  if ( n != SQLITE_OK ) {
    return;
  }

  finished = false;

  retryTimes = 0;
  while (!finished) {
    n = sqlite3_step(statement);
    switch (n) {
      case SQLITE_BUSY : {
        retryTimes++;
        if ( retryTimes > 3 ) {
          finished = false;
          break;
        }
        usleep(25000);
        break;
      }

      case SQLITE_DONE : {
        finished = false;
        break;
      }

      case SQLITE_ROW : {
        IDText                  = QString((char*)sqlite3_column_text(statement, 0));
        LexicalFormText         = QString((char*)sqlite3_column_text(statement, 1));
        TransliteratedFormText  = QString((char*)sqlite3_column_text(statement, 2));
        PartOfSpeechText        = QString((char*)sqlite3_column_text(statement, 3));
        PhoneticSpellingText    = QString((char*)sqlite3_column_text(statement, 4));
        DefinitionText          = QString((char*)sqlite3_column_text(statement, 5));
        OriginText              = QString((char*)sqlite3_column_text(statement, 6));
        UsageText               = QString((char*)sqlite3_column_text(statement, 7));
        finished = true;
        break;
      }
      case SQLITE_ERROR : {
        finished = true;
        break;
      }
      case SQLITE_MISUSE : {
        finished = true;
        break;
      }
    }
  }
  sqlite3_finalize(statement);
}

/*****************************************************************************!
 * Function : CreateHeaderBlock
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::CreateHeaderBlock(void)
{
  QPalette                              pal;
  QLinearGradient                       grad(0, 0, 0, STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT);
  QLabel*                               label;
  
  HeaderBlock = new QWidget(this);
  HeaderBlock->move(0, 0);
  HeaderBlock->resize(STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH, STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT);

  label = new QLabel(HeaderBlock);
  label->setFont(HeaderFont);
  label->move(0, 0);
  label->resize(STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH, STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT);
  label->setText(QString("Strong's Reference - %1").arg(IDText));
  label->setAlignment(Qt::AlignCenter);
  
  grad.setColorAt(0, GradientColorDark);
  grad.setColorAt(1, GradientColorLight);
  pal = HeaderBlock->palette();
  pal.setBrush(QPalette::Window, QBrush(grad));
  HeaderBlock->setAutoFillBackground(true);
  HeaderBlock->setPalette(pal);
}

/*****************************************************************************!
 * Function : CreateLabelBlock
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::CreateLabelBlock(void)
{
  int                                   i;
  int                                   n;
  QLabel*                               label;
  QPalette                              pal;
  QLinearGradient                       grad(0, 0, 0, STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT);
  int                                   y;
  int                                   x;
  int                                   labelWidth;
  int                                   labelHeight;
  QStringList                           labelNames;

  labelNames << "ID"
             << "LEXICAL FORM"
             << "TRANSLITERATED FORM"
             << "PART OF SPEECH"
             << "PHONETIC SPELLING"
             << "DEFINITION"
             << "ORIGIN"
             << "USAGE";
  
  LabelBlock = new QWidget(this);
  LabelBlock->move(0, STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT);
  LabelBlock->resize(STRONGS_REFERENCE_DISPLAY_LABEL_WIDTH,
                     STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT - STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT);

  grad.setColorAt(0, GradientColorLight);
  grad.setColorAt(1, GradientColorDark);
  pal = LabelBlock->palette();
  pal.setBrush(QPalette::Window, QBrush(grad));
  LabelBlock->setAutoFillBackground(true);
  LabelBlock->setPalette(pal);

  labelHeight = 14;
  labelWidth = STRONGS_REFERENCE_DISPLAY_LABEL_WIDTH - 5;

  y = 10;
  x = 0;

  n = labelNames.length();
  for ( i = 0 ; i < n; i++ ) {
    label = new QLabel(LabelBlock);
    label->setFont(LabelFont);
    label->move(x, y);
    label->resize(labelWidth, labelHeight);
    label->setText(labelNames[i] + QString(" :"));
    label->setAlignment(Qt::AlignRight);

    if ( i + 2 < n ) {
      y += labelHeight + 10;
    } else {
      y += 100;
    }
  }
}

/*****************************************************************************!
 * Function : CreateDataBlock
 *****************************************************************************/
void
StrongsReferenceDisplayDialog::CreateDataBlock(void)
{
  QLabel*                               label;
  int                                   labelHeight;
  int                                   x, y;
  int                                   width, height;
  
  DataBlock = new QWidget(this);

  x = STRONGS_REFERENCE_DISPLAY_LABEL_WIDTH;
  y = STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT;

  height = STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT - (STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT + 50);
  width = STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH - STRONGS_REFERENCE_DISPLAY_LABEL_WIDTH;

  labelHeight = 14;

  DataBlock->move(x, y);
  DataBlock->resize(width, height);

  y = 10;
  x = 0;

  CreateDataBlockData(y, width, labelHeight, IDText);
  y += labelHeight + 10;
    
  label = CreateDataBlockData(y, width, labelHeight, LexicalFormText);
  label->setAlignment(Qt::AlignRight);
  label->setFont(ContextualFont);
  y += labelHeight + 10;
  
  CreateDataBlockData(y, width, labelHeight, TransliteratedFormText);
  y += labelHeight + 10;
  
  CreateDataBlockData(y, width, labelHeight, PartOfSpeechText);
  y += labelHeight + 10;
  
  CreateDataBlockData(y, width, labelHeight, PhoneticSpellingText);
  y += labelHeight + 10;
  
  CreateDataBlockData(y, width, labelHeight, DefinitionText);
  y += labelHeight + 10;
  
  CreateDataBlockData(y, width, 90, OriginText);
  y += 100;

  CreateDataBlockData(y, width, 90, UsageText);
}

/*****************************************************************************!
 * Function : CreateDataBlockData
 *****************************************************************************/
QLabel*
StrongsReferenceDisplayDialog::CreateDataBlockData
(int InY, int InWidth, int InHeight, QString InText)
{
  QLabel*                               label;
  label = new QLabel(DataBlock);
  
  label->move(5, InY);
  label->resize(InWidth - 5, InHeight);
  label->setText(InText);
  label->setFont(DataFont);
  label->setAlignment(Qt::AlignLeft);
  label->setWordWrap(true);
  return label;
}

