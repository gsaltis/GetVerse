/*****************************************************************************
 * FILE NAME    : TextDisplayVerseScrollWindow.cpp
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
  setWidget(verseWindow);
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
  int                                   h;
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
  QSize					size;  
  int					width;
  int					height;
  TextDisplayVerseWindow*               w = (TextDisplayVerseWindow*)widget();

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

  connect(verseWindow,
          TextDisplayVerseWindow::SignalWindowChange,
          this,
          TextDisplayVerseScrollWindow::SlotWindowChange);
  
  connect(verseWindow,
          TextDisplayVerseWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayVerseScrollWindow::SlotSetStartupBookmarkInfo);

  connect(verseWindow,
          TextDisplayVerseWindow::SignalChapterArrowSelected,
          this,
          TextDisplayVerseScrollWindow::SlotChapterArrowSelected);

  connect(verseWindow,
          TextDisplayVerseWindow::SignalSetBookmark,
          this,
          TextDisplayVerseScrollWindow::SlotSetBookmark);
  
  connect(verseWindow,
          TextDisplayVerseWindow::SignalGotoBookChapter,
          this,
          TextDisplayVerseScrollWindow::SlotGotoBookChapter);
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotChapterSelected
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
TextDisplayVerseScrollWindow::SlotWindowChange
(int InNewWindow)
{
  emit SignalWindowChange(InNewWindow);  
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);  
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotChapterArrowSelected
(int InChapter)
{
  emit SignalChapterArrowSelected(InChapter);  
}

/*****************************************************************************!
 * Function : SlotSetBookmark
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotSetBookmark
(int InBook, int InChapter, int InVerse, int InWordIndex)
{
  emit SignalSetBookmark(InBook, InChapter, InVerse, InWordIndex);  
}

/*****************************************************************************!
 * Function : SlotGotoBookChapter
 *****************************************************************************/
void
TextDisplayVerseScrollWindow::SlotGotoBookChapter
(BookInfo* InBook, int InChapter)
{
  emit SignalGotoBookChapter(InBook, InChapter);  
}
