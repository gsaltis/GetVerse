/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindowItem.cpp
 * DATE         : September 12 2023
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
#include "TextDisplayViewWindowItem.h"

/*****************************************************************************!
 * Function : TextDisplayViewWindowItem
 *****************************************************************************/
TextDisplayViewWindowItem::TextDisplayViewWindowItem
(QString InText, int InX, int InY, QSize InSize) : QLabel()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setText(InText);
  move(InX, InY);
  resize(InSize);
  linePosition = LinePositionNone;
}

/*****************************************************************************!
 * Function : ~TextDisplayViewWindowItem
 *****************************************************************************/
TextDisplayViewWindowItem::~TextDisplayViewWindowItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewWindowItem::initialize()
{
  textColor = QColor(0, 0, 0);
  selectedColor = QColor(128, 0, 0);
  textBackgroundColor = QColor(255, 255, 255);
  selectedBackgroundColor = QColor(224, 224, 224);
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewWindowItem::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewWindowItem::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindowItem::resizeEvent
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

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayViewWindowItem::enterEvent
(QEnterEvent* InEvent)
{
  QPalette                              pal;
  pal = palette();
  pal.setBrush(QPalette::WindowText, QBrush(selectedColor));
  pal.setBrush(QPalette::Window, QBrush(selectedBackgroundColor));
  setPalette(pal);
  (void)InEvent;
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
TextDisplayViewWindowItem::leaveEvent
(QEvent* InEvent)
{
  QPalette                              pal;
  QFont                                 f = font();
  pal.setBrush(QPalette::WindowText, QBrush(textColor));
  pal.setBrush(QPalette::Window, QBrush(textBackgroundColor));
  setPalette(pal);
  (void)InEvent;
}

/*****************************************************************************!
 * Function : GetLinePosition
 *****************************************************************************/
TextDisplayViewWindowItem::LinePosition
TextDisplayViewWindowItem::GetLinePosition
()
{
  return linePosition;
}

/*****************************************************************************!
 * Function : SetLinePosition
 *****************************************************************************/
void
TextDisplayViewWindowItem::SetLinePosition
(TextDisplayViewWindowItem::LinePosition InPosition)
{
  linePosition = InPosition;
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayViewWindowItem::mousePressEvent
(QMouseEvent* )
{
  int                                   y;
  QPoint                                p;

  p = pos();
  y = p.y();
  TRACE_FUNCTION_INT(y);
}

