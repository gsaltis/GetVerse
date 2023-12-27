/*****************************************************************************
 * FILE NAME    : InterlinearWordDisplay.cpp
 * DATE         : December 24 2023
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
#include "InterlinearWordDisplay.h"

/*****************************************************************************!
 * Function : InterlinearWordDisplay
 *****************************************************************************/
InterlinearWordDisplay::InterlinearWordDisplay
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
 * Function : ~InterlinearWordDisplay
 *****************************************************************************/
InterlinearWordDisplay::~InterlinearWordDisplay
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
InterlinearWordDisplay::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
InterlinearWordDisplay::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
InterlinearWordDisplay::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
InterlinearWordDisplay::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
InterlinearWordDisplay::resizeEvent
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
