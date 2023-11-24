/*****************************************************************************
 * FILE NAME    : BookNameTableScrollArea.cpp
 * DATE         : September 12 2023
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
#include "BookNameTableScrollArea.h"

/*****************************************************************************!
 * Function : BookNameTableScrollArea
 *****************************************************************************/
BookNameTableScrollArea::BookNameTableScrollArea
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
 * Function : ~BookNameTableScrollArea
 *****************************************************************************/
BookNameTableScrollArea::~BookNameTableScrollArea
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookNameTableScrollArea::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BookNameTableScrollArea::CreateSubWindows()
{
  innerTable = new BookNameTableInnerTable();  
  setWidget(innerTable);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BookNameTableScrollArea::InitializeSubWindows()
{
  innerTable = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BookNameTableScrollArea::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   innerTableH;
  int                                   innerTableW;
  int                                   innerTableX;
  int                                   innerTableY;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;

  innerTableH = height;
  innerTableW = width;
  innerTableX = 0;
  innerTableY = 0;
  if ( innerTable ) {
    innerTable->resize(innerTableW, innerTableH);
    innerTable->move(innerTableX, innerTableY);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BookNameTableScrollArea::CreateConnections(void)
{
  connect(innerTable,
          SIGNAL(SignalBookSelected(int)),
          this,
          SLOT(SlotBookSelected(int)));

  connect(this,
          BookNameTableScrollArea::SignalMoveToBookChapter,
          innerTable,
          BookNameTableInnerTable::SlotMoveToBookChapter);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
BookNameTableScrollArea::SlotBookSelected
(int InBookIndex)
{
  emit SignalBookSelected(InBookIndex);
}

/*****************************************************************************!
 * Function : SlotMoveToBookChapter
 *****************************************************************************/
void
BookNameTableScrollArea::SlotMoveToBookChapter
(int InBook, int InChapter, int InVerse)
{
  emit SignalMoveToBookChapter(InBook, InChapter, InVerse);
}
