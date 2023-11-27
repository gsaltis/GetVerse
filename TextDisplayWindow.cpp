/*****************************************************************************
 * FILE NAME    : TextDisplayWindow.cpp
 * DATE         : November 26 2023
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
#include "TextDisplayWindow.h"

/*****************************************************************************!
 * Function : TextDisplayWindow
 *****************************************************************************/
TextDisplayWindow::TextDisplayWindow
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~TextDisplayWindow
 *****************************************************************************/
TextDisplayWindow::~TextDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplayWindow::keyPressEvent
(QKeyEvent* InEvent)
{
  int                                   key;
  Qt::KeyboardModifiers                 mods;
  
  key = InEvent->key();
  mods = InEvent->modifiers();
  
  if ( KeyPress(key, mods) ) {
    return;
  }

  QWidget::keyPressEvent(InEvent);
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayWindow::enterEvent
(QEnterEvent*)
{
  setFocus();
}

/*****************************************************************************!
 * Function : KeyPress
 *****************************************************************************/
bool
TextDisplayWindow::KeyPress
(int InKey, Qt::KeyboardModifiers InModifiers)
{
  if ( InModifiers != Qt::NoModifier ) {
    return false;
  }
  
  if ( InKey == Qt::Key_I ) {
    emit SignalWindowChange(5);
    return true;
  }
  
  if ( InKey == Qt::Key_S ) {
    emit SignalWindowChange(4);
    return true;
  }

  if ( InKey == Qt::Key_R ) {
    emit SignalWindowChange(1);
    return true;
  }
  return false;
}
