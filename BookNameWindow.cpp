/*****************************************************************************
 * FILE NAME    : BookNameWindow.cpp
 * DATE         : September 11 2023
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
#include "BookNameWindow.h"
#include "Common.h"

/*****************************************************************************!
 * Function : BookNameWindow
 *****************************************************************************/
BookNameWindow::BookNameWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(224, 224, 224)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BookNameWindow
 *****************************************************************************/
BookNameWindow::~BookNameWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookNameWindow::initialize()
{
  setFrameShadow(QFrame::Sunken);
  setFrameStyle(QFrame::Panel);
  setLineWidth(1);
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BookNameWindow::CreateSubWindows()
{
  header = new SectionHeader();  
  header->setParent(this);
  header->SetText("Books");
  nameTable = new BookNameTable();
  nameTable->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BookNameWindow::InitializeSubWindows()
{
  header = NULL;  
  nameTable = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BookNameWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   nameTableW;
  int                                   nameTableH;
  int                                   nameTableY;
  int                                   nameTableX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;

  nameTableX = 0;
  nameTableY = SECTION_HEADER_HEIGHT;
  nameTableH = height - SECTION_HEADER_HEIGHT;
  nameTableW = width;
  
  if ( header ) {
    header->resize(width - (SECTION_HEADER_X * 2) , SECTION_HEADER_HEIGHT);
    header->move(SECTION_HEADER_X, SECTION_HEADER_Y);
  }
  if ( nameTable ) {
    nameTable->move(nameTableX, nameTableY);
    nameTable->resize(nameTableW, nameTableH);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BookNameWindow::CreateConnections(void)
{
  connect(nameTable,
          SIGNAL(SignalBookSelected(int)),
          this,
          SLOT(SlotBookSelected(int)));
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
BookNameWindow::SlotBookSelected
(int InBookIndex)
{
  emit SignalBookSelected(InBookIndex);
}
