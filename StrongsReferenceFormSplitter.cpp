/*****************************************************************************
 * FILE NAME    : StrongsReferenceFormSplitter.cpp
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceFormSplitter.h"

/*****************************************************************************!
 * Function : StrongsReferenceFormSplitter
 *****************************************************************************/
StrongsReferenceFormSplitter::StrongsReferenceFormSplitter
() : QSplitter()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(232, 232, 232)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceFormSplitter
 *****************************************************************************/
StrongsReferenceFormSplitter::~StrongsReferenceFormSplitter
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceFormSplitter::initialize()
{
  setOrientation(Qt::Vertical);
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceFormSplitter::CreateSubWindows()
{
  DisplayWindow = new StrongsReferenceDisplayWindow();
  VerseWindow = new StrongsReferenceVerseWindow();

  addWidget(VerseWindow);
  addWidget(DisplayWindow);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceFormSplitter::CreateConnections()
{
  connect(this,
          StrongsReferenceFormSplitter::SignalVerseReferenceClear,
          DisplayWindow,
          StrongsReferenceDisplayWindow::SlotVerseReferenceClear);

  connect(this,
          StrongsReferenceFormSplitter::SignalVerseReferenceClear,
          VerseWindow,
          StrongsReferenceVerseWindow::SlotVerseReferenceClear);

  connect(this,
          StrongsReferenceFormSplitter::SignalVerseReferenceSelected,
          VerseWindow,
          StrongsReferenceVerseWindow::SlotVerseReferenceSelected);

  connect(VerseWindow,
          StrongsReferenceVerseWindow::SignalStrongsReferenceSelected,
          this,
          StrongsReferenceFormSplitter::SlotStrongsReferenceSelected);

  connect(this,
          StrongsReferenceFormSplitter::SignalStrongsReferenceSelected,
          DisplayWindow,
          StrongsReferenceDisplayWindow::SlotStrongsReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceFormSplitter::InitializeSubWindows()
{
  DisplayWindow = NULL;  
  VerseWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceFormSplitter::resizeEvent
(QResizeEvent* )
{
#if 0  
  int                                   VerseWindowW;
  int                                   VerseWindowH;
  int                                   VerseWindowY;
  int                                   VerseWindowX;
  int                                   DisplayWindowW;
  int                                   DisplayWindowH;
  int                                   DisplayWindowY;
  int                                   DisplayWindowX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;

  DisplayWindowX = 0;
  DisplayWindowY = 0;
  DisplayWindowW = width;
  DisplayWindowH = DisplayWindow->size().height();
  DisplayWindow->move(DisplayWindowX, DisplayWindowY);
  DisplayWindow->resize(DisplayWindowW, DisplayWindowH);

  VerseWindowX = 0;
  VerseWindowY = 0;
  VerseWindowW = width;
  VerseWindowH = height;
  VerseWindow->move(VerseWindowX, VerseWindowY);
  VerseWindow->resize(VerseWindowW, VerseWindowH);
#endif  
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceFormSplitter::SlotVerseReferenceClear(void)
{
  emit SignalVerseReferenceClear();  
}

/*****************************************************************************!
 * Function : SlotVerseReferenceSelected
 *****************************************************************************/
void
StrongsReferenceFormSplitter::SlotVerseReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalVerseReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceFormSplitter::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalStrongsReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}
