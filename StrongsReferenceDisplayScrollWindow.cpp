/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayScrollWindow.cpp
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
#include "StrongsReferenceDisplayScrollWindow.h"

/*****************************************************************************!
 * Function : StrongsReferenceDisplayScrollWindow
 *****************************************************************************/
StrongsReferenceDisplayScrollWindow::StrongsReferenceDisplayScrollWindow
() : QScrollArea()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceDisplayScrollWindow
 *****************************************************************************/
StrongsReferenceDisplayScrollWindow::~StrongsReferenceDisplayScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::CreateSubWindows()
{
  WordsWindow = new StrongsReferenceDisplayWordsWindow();
  setWidget(WordsWindow);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::CreateConnections()
{
  connect(this,  
          StrongsReferenceDisplayScrollWindow::SignalVerseReferenceClear,
          WordsWindow,
          StrongsReferenceDisplayWordsWindow::SlotVerseReferenceClear);
  connect(this,
          StrongsReferenceDisplayScrollWindow::SignalStrongsReferenceSelected,
          WordsWindow,
          StrongsReferenceDisplayWordsWindow::SlotStrongsReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::InitializeSubWindows()
{
  WordsWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   WordsWindowW;
  int                                   WordsWindowH;
  int                                   WordsWindowY;
  int                                   WordsWindowX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  WordsWindowX = 0;
  WordsWindowY = 0;
  WordsWindowW = width;
  WordsWindowH = height;
  WordsWindow->move(WordsWindowX, WordsWindowY);
  WordsWindow->resize(WordsWindowW, WordsWindowH);
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::SlotVerseReferenceClear(void)
{
  emit SignalVerseReferenceClear();  
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceDisplayScrollWindow::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalStrongsReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}
