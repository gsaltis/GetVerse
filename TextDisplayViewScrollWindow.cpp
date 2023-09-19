/*****************************************************************************
 * FILE NAME    : TextDisplayViewScrollWindow.cpp
 * DATE         : September 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QScrollBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplayViewScrollWindow
 *****************************************************************************/
TextDisplayViewScrollWindow::TextDisplayViewScrollWindow
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
 * Function : ~TextDisplayViewScrollWindow
 *****************************************************************************/
TextDisplayViewScrollWindow::~TextDisplayViewScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewScrollWindow::initialize()
{
  verticalBar = verticalScrollBar();
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollWindow::CreateSubWindows()
{
  viewWindow = new TextDisplayViewWindow();
  setWidget(viewWindow);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollWindow::InitializeSubWindows()
{
  viewWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   viewWindowH;
  QSize					size;  
  int					width;

  size = InEvent->size();
  width = size.width();
  viewWindowH = viewWindow->GetTableHeight();
  if ( viewWindow ) {
    viewWindow->resize(width, viewWindowH);
  }
}

/*****************************************************************************!
 * Function : ClearText
 *****************************************************************************/
void
TextDisplayViewScrollWindow::ClearText(void)
{
  viewWindow->ClearText();
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QScrollBar*                           vBar;

  vBar = verticalScrollBar();
  vBar->setValue(0);
  emit SignalBookSelected(InBookInfo);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayViewScrollWindow::CreateConnections(void)
{
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          viewWindow,
          SLOT(SlotBookSelected(BookInfo*)));

  connect(viewWindow,
          SIGNAL(SignalHideProgressBar()),
          this,
          SLOT(SlotHideProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalShowProgressBar()),
          this,
          SLOT(SlotShowProgressBar()));
  
  connect(viewWindow,
          SIGNAL(SignalSetProgressBar(int, int)),
          this,
          SLOT(SlotSetProgressBar(int, int)));
  
  connect(viewWindow,
          SIGNAL(SignalUpdateProgressBar(int)),
          this,
          SLOT(SlotUpdateProgressBar(int)));

  connect(viewWindow,
          SIGNAL(SignalWordCountChanged(int)),
          this,
          SLOT(SlotWordCountChanged(int)));

  connect(viewWindow,
          SIGNAL(SignalSentenceCountChanged(int)),
          this,
          SLOT(SlotSentenceCountChanged(int)));

  connect(viewWindow,
          SIGNAL(SignalVerseCountChanged(int)),
          this,
          SLOT(SlotVerseCountChanged(int)));

  connect(this,
          SIGNAL(SignalSetSentenceMode()),
          viewWindow,
          SLOT(SlotSetSentenceMode()));
  connect(this,
          SIGNAL(SignalSetEditMode()),
          viewWindow,
          SLOT(SlotSetEditMode()));
  connect(this,
          SIGNAL(SignalSetReferenceMode()),
          viewWindow,
          SLOT(SlotSetReferenceMode()));
  connect(this,
          SIGNAL(SignalSetBlockMode()),
          viewWindow,
          SLOT(SlotSetBlockMode()));

  connect(verticalBar,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(SlotVerticalScrolled(int)));

  connect(this,
          SIGNAL(SignalVerticalScrolled()),
          viewWindow,
          SLOT(SlotVerticalScrolled()));
}

/*****************************************************************************!
 * Function : SlotHideProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotHideProgressBar(void)
{
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : SlotShowProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotShowProgressBar(void)
{
  emit SignalShowProgressBar();
}

/*****************************************************************************!
 * Function : SlotUpdateProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotUpdateProgressBar
(int InValue)
{
  emit SignalUpdateProgressBar(InValue);
}

/*****************************************************************************!
 * Function : SlotSetProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetProgressBar
(int InMin, int InMax)
{
  emit SignalSetProgressBar(InMin, InMax);
}

/*****************************************************************************!
 * Function : SlotWordCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotWordCountChanged
(int InWordCount)
{
  emit SignalWordCountChanged(InWordCount);
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetSentenceMode(void)
{
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetBlockMode(void)
{
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetReferenceMode(void)
{
  emit SignalSetReferenceMode();
}

/*****************************************************************************!
 * Function : SlotSetEditMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetEditMode(void)
{
  emit SignalSetEditMode();
}

/*****************************************************************************!
 * Function : SlotVerseCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotVerseCountChanged
(int InVerseCount)
{
  emit SignalVerseCountChanged(InVerseCount);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}

/*****************************************************************************!
 * Function : SlotVerticalScrolled
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotVerticalScrolled
(int)
{
  emit SignalVerticalScrolled();
}

