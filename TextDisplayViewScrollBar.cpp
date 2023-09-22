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
  ChapterScrollingMode = false;
  MouseDown = false;
  setMouseTracking(true);
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
  MouseDown = true;
  setFocus();
  grabKeyboard();
  MouseChapterSelect(p);
}

/*****************************************************************************!
 * Function : mouseReleaseEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::mouseReleaseEvent
(QMouseEvent* InEvent)
{
  if ( ChapterScrollingMode ) {
    ChapterScrollingMode = false;
    MouseDown = false;
    repaint();
    return;
  }

  QScrollBar::mouseReleaseEvent(InEvent);
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
    if ( ChapterScrollingMode ) {
      ChapterScrollingMode = false;
      repaint();
    }
    QScrollBar::mouseMoveEvent(InEvent);
    return;
  }

  if ( MouseDown ) {
    ChapterScrollingMode = true;
    currentChapter = (y * ChapterCount / height) + 1;
    ChapterScrollingMode = true;
    emit SignalChapterSelected(currentChapter);
    currentMouseLocation = p;
    repaint();
  }
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
  repaint();
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::leaveEvent
(QEvent* InEvent)
{
  if ( ChapterScrollingMode ) {
    ChapterScrollingMode = false;
    MouseDown = false;
    repaint();
  }
  QScrollBar::leaveEvent(InEvent);
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::paintEvent
(QPaintEvent* InEvent)
{
  int                                   height;
  qreal                                 s2, s3, s4;
  
  if ( ChapterScrollingMode ) {
    QSize                               s = size();
    QPainter                            painter(this);
    QBrush                              brush;
    int                                 y;

    y = currentMouseLocation.y();
    height = s.height();

    s3 = (qreal)y / (qreal)height;
    s2 = s3 - .02;
    s4 = s3 + .02;

    if ( s2 < 0 ) {
      s2 = 0;
    }

    if ( s3 < 0 ) {
      s3 = 0;
    }

    if (  s3 > 1 ) {
      s3 = 1;
    }
    
    if ( s4 < 0 || s4 > 1 ) {
      s4 = 1;
    }
    QLinearGradient                     grad(0, 0, 0, s.height());
    grad.setColorAt(0, QColor(255, 255, 255));
    grad.setColorAt(s2, QColor(128, 128, 128));
    grad.setColorAt(s3, QColor(0, 0, 0));
    grad.setColorAt(s4, QColor(128, 128, 128));
    grad.setColorAt(1, QColor(255, 255, 255));
    
    
    brush = QBrush(grad);
    painter.setBrush(brush);
    
    painter.drawRect(0, 0, s.width(), s.height());
    painter.end();
    return;
  }
  QScrollBar::paintEvent(InEvent);
}

/*****************************************************************************!
 * Function : keyReleaseEvent
 *****************************************************************************/
void
TextDisplayViewScrollBar::keyReleaseEvent
(QKeyEvent* InEvent)
{
  if ( ChapterScrollingMode ) {
    ChapterScrollingMode = false;
    MouseDown = false;
    repaint();
  }

  return QScrollBar::keyReleaseEvent(InEvent);
}
