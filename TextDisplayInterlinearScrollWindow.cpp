/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearScrollWindow.cpp
 * DATE         : December 18 2023
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
#include "TextDisplayInterlinearScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearScrollWindow
 *****************************************************************************/
TextDisplayInterlinearScrollWindow::TextDisplayInterlinearScrollWindow
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
 * Function : ~TextDisplayInterlinearScrollWindow
 *****************************************************************************/
TextDisplayInterlinearScrollWindow::~TextDisplayInterlinearScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::CreateSubWindows()
{
  verseWindow = new TextDisplayInterlinearWindow();  
  setWidget(verseWindow);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::InitializeSubWindows()
{
  verseWindow = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   h;
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
  QSize					size;  
  int					width;
  int					height;
  TextDisplayInterlinearWindow*               w = (TextDisplayInterlinearWindow*)widget();

  size = InEvent->size();
  width = size.width();
  height = verseWindow->ArrangeItems(width);
  h = size.height();
  if ( h > height ) {
    height = h;
  }
  verseWindowX = 0;
  verseWindowY = 0;
  verseWindowW = width;
  verseWindowH = height;
  w->move(verseWindowX, verseWindowY);
  w->resize(verseWindowW, verseWindowH);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotBookSelected
(BookInfo* InBook)
{
  emit SignalBookSelected(InBook);  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::CreateConnections(void)
{
  connect(this,
          TextDisplayInterlinearScrollWindow::SignalBookSelected,
          verseWindow,
          TextDisplayInterlinearWindow::SlotBookSelected);

  connect(this,
          TextDisplayInterlinearScrollWindow::SignalChapterSelected,
          verseWindow,
          TextDisplayInterlinearWindow::SlotChapterSelected);

  connect(verseWindow,
          TextDisplayInterlinearWindow::SignalWindowChange,
          this,
          TextDisplayInterlinearScrollWindow::SlotWindowChange);
  
  connect(verseWindow,
          TextDisplayInterlinearWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayInterlinearScrollWindow::SlotSetStartupBookmarkInfo);
  connect(verseWindow,
          TextDisplayInterlinearWindow::SignalChapterArrowSelected,
          this,
          TextDisplayInterlinearScrollWindow::SlotChapterArrowSelected);
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotChapterSelected
(int InChapter)
{
  int                                   height;
  int                                   width;
  emit SignalChapterSelected(InChapter);
  width = size().width();
  height = verseWindow->ArrangeItems(width);
  verseWindow->resize(width, height);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotWindowChange
(int InNewWindow)
{
  emit SignalWindowChange(InNewWindow);  
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);  
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotChapterArrowSelected
(int InChapter)
{
  emit SignalChapterArrowSelected(InChapter);  
}
