/*****************************************************************************
 * FILE NAME    : TextDisplayViewScrollBar.cpp
 * DATE         : September 21 2023
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
#include "TextDisplayViewScrollBar.h"
#include "Trace.h"

/*****************************************************************************!
 * Function : TextDisplayViewScrollBar
 *****************************************************************************/
TextDisplayViewScrollBar::TextDisplayViewScrollBar
() : QScrollBar()
{
  ChapterCount = 0;
  setMouseTracking(true);
  setToolTip(QString("Hi Mom"));
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayViewScrollBar
 *****************************************************************************/
TextDisplayViewScrollBar::~TextDisplayViewScrollBar
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewScrollBar::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollBar::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollBar::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::resizeEvent
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
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::mousePressEvent
(QMouseEvent* InEvent)
{
  QPoint                                p = InEvent->pos();
  Qt::KeyboardModifiers                 modifiers;

  modifiers = InEvent->modifiers();
  if ( modifiers != Qt::ControlModifier ) {
    QScrollBar::mousePressEvent(InEvent);
    return;
  }
  MouseChapterSelect(p);
}

/*****************************************************************************!
 * Function : MouseChapterSelect
 *****************************************************************************/
void
TextDisplayViewScrollBar::MouseChapterSelect
(QPoint InPoint)
{
  int                                   currentChapter;
  QSize                                 s;
  int                                   height;
  int                                   y;

  s = size();
  height = s.height();
  y = InPoint.y();
  
  currentChapter = (y * ChapterCount / height) + 1;
  emit SignalChapterSelected(currentChapter);
}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::mouseMoveEvent
(QMouseEvent* InEvent)
{
  int                                   currentChapter;
  QPoint                                p = InEvent->pos();
  QSize                                 s = size();
  int                                   height = s.height();
  int                                   y = p.y();

  Qt::KeyboardModifiers                 modifiers;

  modifiers = InEvent->modifiers();
  if ( modifiers != Qt::ControlModifier ) {
    QScrollBar::mousePressEvent(InEvent);
    return;
  }
  currentChapter = (y * ChapterCount / height) + 1;
  emit SignalChapterScrolled(currentChapter);
}

/*****************************************************************************!
 * Function : GetChapterCount
 *****************************************************************************/
int
TextDisplayViewScrollBar::GetChapterCount(void)
{
  return ChapterCount;  
}

/*****************************************************************************!
 * Function : SetChapterCount
 *****************************************************************************/
void
TextDisplayViewScrollBar::SetChapterCount
(int InChapterCount)
{
  ChapterCount = InChapterCount;  
}
