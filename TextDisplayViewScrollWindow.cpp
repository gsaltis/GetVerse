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
}
