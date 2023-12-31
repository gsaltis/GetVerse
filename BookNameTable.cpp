/*****************************************************************************
 * FILE NAME    : BookNameTable.cpp
 * DATE         : September 11 2023
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
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameTable.h"
#include "Common.h"

/*****************************************************************************!
 * Function : BookNameTable
 *****************************************************************************/
BookNameTable::BookNameTable
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
 * Function : ~BookNameTable
 *****************************************************************************/
BookNameTable::~BookNameTable
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookNameTable::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BookNameTable::CreateSubWindows()
{
  scrollArea = new BookNameTableScrollArea();  
  scrollArea->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BookNameTable::InitializeSubWindows()
{
  scrollArea = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BookNameTable::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  if ( scrollArea ) {
    scrollArea->move(BOOK_NAME_TABLE_SCROLL_AREA_X,
                     BOOK_NAME_TABLE_SCROLL_AREA_Y);
    scrollArea->resize(width, height);
  }
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
BookNameTable::SlotBookSelected
(int InBookIndex)
{
  emit SignalBookSelected(InBookIndex);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BookNameTable::CreateConnections(void)
{
  connect(scrollArea,
          SIGNAL(SignalBookSelected(int)),
          this,
          SLOT(SlotBookSelected(int)));
  connect(this,
          BookNameTable::SignalMoveToBookChapter,
          scrollArea,
          BookNameTableScrollArea::SlotMoveToBookChapter);
}

/*****************************************************************************!
 * Function : SlotMoveToBookChapter
 *****************************************************************************/
void
BookNameTable::SlotMoveToBookChapter
(int InBook, int InChapter, int InVerse)
{
  emit SignalMoveToBookChapter(InBook, InChapter, InVerse);
}
