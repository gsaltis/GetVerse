/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWordsWindow.cpp
 * DATE         : December 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayWordsWindow.h"

/*****************************************************************************!
 * Function : StrongsReferenceDisplayWordsWindow
 *****************************************************************************/
StrongsReferenceDisplayWordsWindow::StrongsReferenceDisplayWordsWindow
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
 * Function : ~StrongsReferenceDisplayWordsWindow
 *****************************************************************************/
StrongsReferenceDisplayWordsWindow::~StrongsReferenceDisplayWordsWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::CreateSubWindows()
{
  Display = new StrongsReferenceDisplayWord();  
  Display->setParent(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::CreateConnections()
{
  connect(this,  
          StrongsReferenceDisplayWordsWindow::SignalVerseReferenceClear,
          Display,
          StrongsReferenceDisplayWord::SlotVerseReferenceClear);
  connect(this,
          StrongsReferenceDisplayWordsWindow::SignalStrongsReferenceSelected,
          Display,
          StrongsReferenceDisplayWord::SlotStrongsReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::InitializeSubWindows()
{
  Display = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   DisplayW;
  int                                   DisplayH;
  int                                   DisplayY;
  int                                   DisplayX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  DisplayX = 5;
  DisplayY = 5;
  DisplayW = width - 10;
  DisplayH = height - 10;
  Display->move(DisplayX, DisplayY);
  Display->resize(DisplayW, DisplayH);
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::SlotVerseReferenceClear(void)
{
  emit SignalVerseReferenceClear();  
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceDisplayWordsWindow::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalStrongsReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}
