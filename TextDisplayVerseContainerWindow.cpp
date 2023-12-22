/*****************************************************************************
 * FILE NAME    : TextDisplayVerseContainerWindow.cpp
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
#include "TextDisplayVerseContainerWindow.h"

/*****************************************************************************!
 * Function : TextDisplayVerseContainerWindow
 *****************************************************************************/
TextDisplayVerseContainerWindow::TextDisplayVerseContainerWindow
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
 * Function : ~TextDisplayVerseContainerWindow
 *****************************************************************************/
TextDisplayVerseContainerWindow::~TextDisplayVerseContainerWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::CreateSubWindows()
{
  verseWindow = new TextDisplayVerseScrollWindow();  
  verseWindow->setParent(this);
  header = new ChapterHeaderWindow("Chapter", this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::InitializeSubWindows()
{
  verseWindow = NULL;
  header = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   headerW;
  int                                   headerH;
  int                                   headerY;
  int                                   headerX;
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
  verseWindowY = CHAPTER_HEADER_WINDOW_HEIGHT;
  verseWindowW = width;
  verseWindowH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  verseWindow->move(verseWindowX, verseWindowY);
  verseWindow->resize(verseWindowW, verseWindowH);

  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = CHAPTER_HEADER_WINDOW_HEIGHT;
  header->move(headerX, headerY);
  header->resize(headerW, headerH);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::CreateConnections(void)
{
  connect(this,
          TextDisplayVerseContainerWindow::SignalBookSelected,
          verseWindow,
          TextDisplayVerseScrollWindow::SlotBookSelected);
  connect(this,
          TextDisplayVerseContainerWindow::SignalChapterSelected,
          verseWindow,
          TextDisplayVerseScrollWindow::SlotChapterSelected);
  connect(verseWindow,
          TextDisplayVerseScrollWindow::SignalWindowChange,
          this,
          TextDisplayVerseContainerWindow::SlotWindowChange);
  connect(verseWindow,
          TextDisplayVerseScrollWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayVerseContainerWindow::SlotSetStartupBookmarkInfo);
  connect(verseWindow,
          TextDisplayVerseScrollWindow::SignalChapterArrowSelected,
          this,
          TextDisplayVerseContainerWindow::SlotChapterArrowSelected);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::SlotBookSelected
(BookInfo* InBook)
{
  emit SignalBookSelected(InBook);
  emit SignalChapterSelected(1);
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::SlotChapterSelected
(int InChapter)
{
  QString                               chapterText;

  chapterText = QString("Chapter %1").arg(InChapter);
  header->SetText(chapterText);
  emit SignalChapterSelected(InChapter);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::SlotWindowChange
(int InNewWindow)
{
  emit SignalWindowChange(InNewWindow);  
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);  
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayVerseContainerWindow::SlotChapterArrowSelected
(int InChapter)
{
  emit SignalChapterArrowSelected(InChapter);  
}
