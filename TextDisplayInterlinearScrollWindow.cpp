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
#include <QScrollBar>

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
  PerformResize(InEvent->size());
}

/*****************************************************************************!
 * Function : PerformResize
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::PerformResize
(QSize InSize)
{
  int                                   h;
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
  int					width;
  int					height;
  TextDisplayInterlinearWindow*               w = (TextDisplayInterlinearWindow*)widget();

  width = InSize.width();
  height = verseWindow->ArrangeItems(width);
  h = InSize.height();
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
  verticalScrollBar()->setSliderPosition(0);
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

  connect(verseWindow,
          TextDisplayInterlinearWindow::SignalSelectStrongsWord,
          this,
          TextDisplayInterlinearScrollWindow::SlotSelectStrongsWord);

  connect(this,
          TextDisplayInterlinearScrollWindow::SignalEnglishChanged,
          verseWindow,
          TextDisplayInterlinearWindow::SlotEnglishChanged);

  connect(this,
          TextDisplayInterlinearScrollWindow::SignalTransliterateChanged,
          verseWindow,
          TextDisplayInterlinearWindow::SlotTransliterateChanged);
  connect(this,
          TextDisplayInterlinearScrollWindow::SignalStrongsChanged,
          verseWindow,
          TextDisplayInterlinearWindow::SlotStrongsChanged);
  connect(this,
          TextDisplayInterlinearScrollWindow::SignalMorphologyChanged,
          verseWindow,
          TextDisplayInterlinearWindow::SlotMorphologyChanged);
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

  verticalScrollBar()->setSliderPosition(0);
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

/*****************************************************************************!
 * Function : SlotSelectStrongsWord
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotSelectStrongsWord
(QString InStrongsWord)
{
  emit SignalSelectStrongsWord(InStrongsWord);
  PerformResize(size());
}

/*****************************************************************************!
 * Function : SlotEnglishChanged
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotEnglishChanged
(bool InSet)
{
  emit SignalEnglishChanged(InSet);  
  PerformResize(size());
}

/*****************************************************************************!
 * Function : SlotTransliterateChanged
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotTransliterateChanged
(bool InSet)
{
  
  emit SignalTransliterateChanged(InSet);
  PerformResize(size());
}

/*****************************************************************************!
 * Function : SlotStrongsChanged
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotStrongsChanged
(bool InSet)
{
  emit SignalStrongsChanged(InSet);  
  PerformResize(size());
}

/*****************************************************************************!
 * Function : SlotMorphologyChanged
 *****************************************************************************/
void
TextDisplayInterlinearScrollWindow::SlotMorphologyChanged
(bool InSet)
{
  emit SignalMorphologyChanged(InSet);  
  PerformResize(size());
}
