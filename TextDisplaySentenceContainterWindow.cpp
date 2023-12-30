/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceContainterWindow.cpp
 * DATE         : November 12 2023
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplaySentenceContainterWindow.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceContainterWindow
 *****************************************************************************/
TextDisplaySentenceContainterWindow::TextDisplaySentenceContainterWindow
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
 * Function : ~TextDisplaySentenceContainterWindow
 *****************************************************************************/
TextDisplaySentenceContainterWindow::~TextDisplaySentenceContainterWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::initialize()
{
  bookInfo = NULL;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::CreateSubWindows()
{
  sentenceWindow = new TextDisplaySentenceScrollWindow();
  sentenceWindow->setParent(this);
  headerWindow = new ChapterHeaderWindow(QString("Chapter 999"), this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::InitializeSubWindows()
{
  sentenceWindow = NULL;  
  headerWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   sentenceWindowX;
  int                                   sentenceWindowY;
  int                                   sentenceWindowW;
  int                                   sentenceWindowH;
  int                                   headerWindowX;
  int                                   headerWindowY;
  int                                   headerWindowW;
  int                                   headerWindowH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  headerWindowX = 0;
  headerWindowY = 0;
  headerWindowW = width;
  headerWindowH = CHAPTER_HEADER_WINDOW_HEIGHT;

  sentenceWindowX = 0;
  sentenceWindowY = headerWindowY + headerWindowH;
  sentenceWindowW = width;
  sentenceWindowH = height - sentenceWindowY;
  
  if ( sentenceWindow ) {
    sentenceWindow->move(sentenceWindowX, sentenceWindowY);
    sentenceWindow->resize(sentenceWindowW, sentenceWindowH);
  }
  if ( headerWindow ) {
    headerWindow->move(headerWindowX, headerWindowY);
    headerWindow->resize(headerWindowW, headerWindowH);
  }
}

/*****************************************************************************!
 * Function : SlotBookSet
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::SlotBookSet
(BookInfo* InBookInfo)
{
  QString                               name;
  QString                               chapterName;

  bookInfo = InBookInfo;

  name = bookInfo ? bookInfo->GetName() : QString();
  chapterName = QString("%1 11").arg(name);
  emit SignalChapterTextChanged(chapterName);
  emit SignalBookSet(InBookInfo);
}

/*****************************************************************************!
 * Function : SlotChapterSet
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::SlotChapterSet
(int InChapter)
{
  QString                               text;
  QString                               name;

  name = bookInfo ? bookInfo->GetName() : QString();
  
  text = QString("%1 %2").arg(name).arg(InChapter);
  emit SignalChapterTextChanged(text);
  emit SignalChapterSet(InChapter);
  emit SignalChapterArrowSelected(InChapter);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::CreateConnections(void)
{
  connect(sentenceWindow,
          TextDisplaySentenceScrollWindow::SignalWindowChange,
          this,
          TextDisplaySentenceContainterWindow::SlotWindowChange);

  connect(sentenceWindow,
          TextDisplaySentenceScrollWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplaySentenceContainterWindow::SlotSetStartupBookmarkInfo);
  
  connect(sentenceWindow,
          TextDisplaySentenceScrollWindow::SignalSentenceCountChanged,
          this,
          TextDisplaySentenceContainterWindow::SlotSentenceCountChanged);
  
  connect(this,
          TextDisplaySentenceContainterWindow::SignalChapterTextChanged,
          headerWindow,
          ChapterHeaderWindow::SlotTextChanged);

  connect(this,
          TextDisplaySentenceContainterWindow::SignalBookSet,
          sentenceWindow,
          TextDisplaySentenceScrollWindow::SlotBookSelected);

  connect(this,
          TextDisplaySentenceContainterWindow::SignalChapterSet,
          sentenceWindow,
          TextDisplaySentenceScrollWindow::SlotChapterChanged);

  connect(sentenceWindow,
          TextDisplaySentenceScrollWindow::SignalChapterArrowSelected,
          this,
          TextDisplaySentenceContainterWindow::SlotChapterSet);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::SlotWindowChange
(int InType)
{
  emit SignalWindowChange(InType);
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);
}
