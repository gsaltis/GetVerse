/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceScrollWindow.cpp
 * DATE         : November 24 2023
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
#include "TextDisplaySentenceScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceScrollWindow
 *****************************************************************************/
TextDisplaySentenceScrollWindow::TextDisplaySentenceScrollWindow
() : QScrollArea()
{
  QPalette pal;
  pal = QScrollArea::palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 224)));
  QScrollArea::setPalette(pal);
  QScrollArea::setAutoFillBackground(true);
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

  connect(sentenceWindow,
          SIGNAL(SignalWindowChange(int)),
          this,
          SLOT(SlotWindowChange(int)));
  
  connect(sentenceWindow,
          SIGNAL(SignalChapterArrowSelected(int)),
          this,
          SLOT(SlotChapterArrowSelected(int)));

  connect(sentenceWindow,
          SIGNAL(SignalSentenceCountChanged(int)),
          this,
          SLOT(SlotSentenceCountChanged(int)));
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
  sentenceWindow->SlotBookSelected(InBookInfo);
  sentenceWindow->CreateDisplayItems();
  sentenceWindow->resize(QScrollArea::size());
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotChapterChanged
(int InChapter)
{
  sentenceWindow->SlotChapterChanged(InChapter);
  sentenceWindow->CreateDisplayItems();
  sentenceWindow->resize(QScrollArea::size());
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
  height= sentenceWindow->ArrangeItems(width);
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

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::SlotWindowChange
(int InType)
{
  emit SignalWindowChange(InType);
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::keyPressEvent
(QKeyEvent* InEvent)
{
  int                                   key;
  Qt::KeyboardModifiers                 mods;

  key = InEvent->key();
  mods = InEvent->modifiers();

  if ( sentenceWindow->KeyPress(key, mods) ) {
    return;
  }

  TRACE_FUNCTION_LOCATION();
  QScrollArea::keyPressEvent(InEvent);
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplaySentenceScrollWindow::enterEvent
(QEnterEvent*)
{
  setFocus();
}

