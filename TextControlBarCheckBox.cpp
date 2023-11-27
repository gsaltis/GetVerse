/*****************************************************************************
 * FILE NAME    : TextControlBarCheckBox.cpp
 * DATE         : November 27 2023
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
#include "TextControlBarCheckBox.h"

/*****************************************************************************!
 * Function : TextControlBarCheckBox
 *****************************************************************************/
TextControlBarCheckBox::TextControlBarCheckBox
(QWidget* InParent, bool InChecked) : QFrame(InParent)
{
  initialize();
  Checked = InChecked;
}

/*****************************************************************************!
 * Function : ~TextControlBarCheckBox
 *****************************************************************************/
TextControlBarCheckBox::~TextControlBarCheckBox
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextControlBarCheckBox::initialize()
{
  CheckedColor = QColor(128, 128, 128);
  Checked = false;
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextControlBarCheckBox::paintEvent
(QPaintEvent* )
{
  QColor                                color;
  QPainter                              painter(this);
  QSize                                 s;
  QPen                                  pen;
  QBrush                                brush;
  QRect                                 rect;
  
  pen = QPen(QColor(0, 0, 0));
  s = size();
  
  rect = QRect(QPoint(0, 0), s);
  color = QColor(255, 255, 255);
  if ( Checked ) {
    color = CheckedColor;
  }
  brush = QBrush(color);
  painter.setBrush(brush);
  painter.setPen(pen);
  painter.drawRect(rect);
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextControlBarCheckBox::mousePressEvent
(QMouseEvent* InEvent)
{
  Qt::MouseButton                       button;
  Qt::KeyboardModifiers                 mods;

  button = InEvent->button();
  mods = InEvent->modifiers();

  if ( mods != Qt::NoModifier ) {
    QFrame::mousePressEvent(InEvent);
    return;
  }

  if ( button == Qt::LeftButton ) {
    ToggleCheck();
    return;
  }

  QFrame::mousePressEvent(InEvent);
}

/*****************************************************************************!
 * Function : ToggleCheck
 *****************************************************************************/
void
TextControlBarCheckBox::ToggleCheck
()
{
  if ( Checked ) {
    Checked = false;
  } else {
    Checked = true;
  }

  repaint();
  emit SignalChecked(Checked);
}

/*****************************************************************************!
 * Function : SetChecked
 *****************************************************************************/
void
TextControlBarCheckBox::SetChecked
(bool InChecked)
{
  Checked = InChecked;
  repaint();
}

/*****************************************************************************!
 * Function : SetChecked
 *****************************************************************************/
void
TextControlBarCheckBox::CheckChanged
(bool InChecked)
{
  Checked = InChecked;
  repaint();
  emit SignalChecked(Checked);
}

