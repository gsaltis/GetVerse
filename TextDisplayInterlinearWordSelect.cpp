/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearWordSelect.cpp
 * DATE         : December 27 2023
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
#include "TextDisplayInterlinearWordSelect.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearWordSelect
 *****************************************************************************/
TextDisplayInterlinearWordSelect::TextDisplayInterlinearWordSelect
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(240, 240, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearWordSelect
 *****************************************************************************/
TextDisplayInterlinearWordSelect::~TextDisplayInterlinearWordSelect
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}
