/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceContainterWindow.cpp
 * DATE         : November 12 2023
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
#include "TextDisplaySentenceContainterWindow.h"
#include "Trace.h"

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
  sentenceWindow = new TextDisplaySentenceWindow(this);
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
  QString                       chapterName;

  chapterName = QString("Chapter 1");
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
  QString                       text;

  text = QString("Chapter %1").arg(InChapter);
  emit SignalChapterTextChanged(text);
  emit SignalChapterSet(InChapter);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplaySentenceContainterWindow::CreateConnections(void)
{
  connect(this,
          TextDisplaySentenceContainterWindow::SignalChapterTextChanged,
          headerWindow,
          ChapterHeaderWindow::SlotTextChanged);

  connect(this,
          TextDisplaySentenceContainterWindow::SignalBookSet,
          sentenceWindow,
          TextDisplaySentenceWindow::SlotBookSelected);

  connect(this,
          TextDisplaySentenceContainterWindow::SignalChapterSet,
          sentenceWindow,
          TextDisplaySentenceWindow::SlotChapterChanged);
}
