/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWindow.cpp
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
#include "StrongsReferenceDisplayWindow.h"
#include "BookInfo.h"

/*****************************************************************************!
 * Function : StrongsReferenceDisplayWindow
 *****************************************************************************/
StrongsReferenceDisplayWindow::StrongsReferenceDisplayWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceDisplayWindow
 *****************************************************************************/
StrongsReferenceDisplayWindow::~StrongsReferenceDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::initialize()
{
  setMaximumHeight(200);
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::CreateSubWindows()
{
  ScrollArea = new StrongsReferenceDisplayScrollWindow();  
  ScrollArea->setParent(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::CreateConnections()
{
  connect(this,  
          StrongsReferenceDisplayWindow::SignalVerseReferenceClear,
          ScrollArea,
          StrongsReferenceDisplayScrollWindow::SlotVerseReferenceClear);
  connect(this,
          StrongsReferenceDisplayWindow::SignalStrongsReferenceSelected,
          ScrollArea,
          StrongsReferenceDisplayScrollWindow::SlotStrongsReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::InitializeSubWindows()
{
  ScrollArea = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   ScrollAreaW;
  int                                   ScrollAreaH;
  int                                   ScrollAreaY;
  int                                   ScrollAreaX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  ScrollAreaX = 0;
  ScrollAreaY = 0;
  ScrollAreaW = width;
  ScrollAreaH = height;
  ScrollArea->move(ScrollAreaX, ScrollAreaY);
  ScrollArea->resize(ScrollAreaW, ScrollAreaH);
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::SlotVerseReferenceClear(void)
{
  emit SignalVerseReferenceClear();
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceDisplayWindow::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalStrongsReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);
}
