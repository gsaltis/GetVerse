/*****************************************************************************
 * FILE NAME    : TextDisplayVerseScrollWindow.cpp
 * DATE         : December 18 2023
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
#include "TextDisplayVerseScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplayVerseScrollWindow
 *****************************************************************************/
TextDisplayVerseScrollWindow::TextDisplayVerseScrollWindow
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
 * Function : ~TextDisplayVerseScrollWindow
 *****************************************************************************/
TextDisplayVerseScrollWindow::~TextDisplayVerseScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::CreateSubWindows()
{
  verseWindow = new TextDisplayVerseWindow();  
  verseWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::InitializeSubWindows()
{
  verseWindow = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  verseWindowX = 0;
  verseWindowY = 0;
  verseWindowW = width;
  verseWindowH = height;
  verseWindow->move(verseWindowX, verseWindowY);
  verseWindow->resize(verseWindowW, verseWindowH);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotBookSelected
(BookInfo* InBook)
{
  emit SignalBookSelected(InBook);  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::CreateConnections(void)
{
  connect(this,
          TextDisplayVerseScrollWindow::SignalBookSelected,
          verseWindow,
          TextDisplayVerseWindow::SlotBookSelected);
  connect(this,
          TextDisplayVerseScrollWindow::SignalChapterSelected,
          verseWindow,
          TextDisplayVerseWindow::SlotChapterSelected);
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotChapterSelected
(int InChapter)
{
  emit SignalChapterSelected(InChapter);  
}
