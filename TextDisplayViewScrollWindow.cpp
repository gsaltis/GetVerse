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
  viewWindowH = viewWindow->ArrangeElements(width);
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
