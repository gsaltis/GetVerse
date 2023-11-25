/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceScrollWindow.cpp
 * DATE         : November 24 2023
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
#include "TextDisplaySentenceScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceScrollWindow
 *****************************************************************************/
TextDisplaySentenceScrollWindow::TextDisplaySentenceScrollWindow
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
 * Function : ~TextDisplaySentenceScrollWindow
 *****************************************************************************/
TextDisplaySentenceScrollWindow::~TextDisplaySentenceScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::CreateSubWindows()
{
  sentenceWindow = new TextDisplaySentenceWindow();
  setWidget(sentenceWindow);
  setWidgetResizable(false);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::CreateConnections
()
{
  connect(this,
          TextDisplaySentenceScrollWindow::SignalBookSelected,
          sentenceWindow,
          TextDisplaySentenceWindow::SlotBookSelected);
  
  connect(this,
          TextDisplaySentenceScrollWindow::SignalChapterChanged,
          sentenceWindow,
          TextDisplaySentenceWindow::SlotChapterChanged);
  connect(sentenceWindow,
          TextDisplaySentenceWindow::SignalChapterArrowSelected,
          this,
          TextDisplaySentenceScrollWindow::SlotChapterArrowSelected);
  connect(sentenceWindow,
          TextDisplaySentenceWindow::SignalSentenceCountChanged,
          this,
          TextDisplaySentenceScrollWindow::SlotSentenceCountChanged);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  int                           windowHeight;

  sentenceWindow->SlotBookSelected(InBookInfo);
  sentenceWindow->CreateDisplayItems();
  windowHeight= sentenceWindow->ArrangeItems();
  sentenceWindow->resize(size().width(), windowHeight);
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotChapterChanged
(int InChapter)
{
  int                           windowHeight;

  sentenceWindow->SlotChapterChanged(InChapter);
  sentenceWindow->CreateDisplayItems();
  windowHeight= sentenceWindow->ArrangeItems();
  sentenceWindow->resize(size().width(), windowHeight);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  TextDisplaySentenceWindow*            w = (TextDisplaySentenceWindow*)widget();
  int                                   width;
  int                                   height;

  width = InEvent->size().width();
  height = w->GetWindowHeight();
  w->resize(width, height);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotChapterArrowSelected
(int InChapter)
{
  emit SignalChapterArrowSelected(InChapter);
}
