/*****************************************************************************
 * FILE NAME    : TextDisplayVerseReferenceItem.cpp
 * DATE         : December 21 2023
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
#include "TextDisplayVerseReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayVerseReferenceItem
 *****************************************************************************/
TextDisplayVerseReferenceItem::TextDisplayVerseReferenceItem
(int InVerseNumber, int InX, int InY, QWidget* InParent) : QLabel(InParent)
{
  QPalette pal;
  DisplayFont = QFont("Arial", 10, QFont::Bold);
  DisplayColor = QColor(64, 0, 0);
  VerseNumber = InVerseNumber;

  pal = palette();
  pal.setBrush(QPalette::WindowText, QBrush(DisplayColor));
  setPalette(pal);
  setAutoFillBackground(true);

  setFont(DisplayFont);

  move(InX, InY);
  resize(TEXT_DISPLAY_VERSE_REFERENCE_ITEM_WIDTH, TEXT_DISPLAY_VERSE_REFERENCE_ITEM_HEIGHT);
  
  setAlignment(Qt::AlignRight);
  setText(QString("%1:").arg(VerseNumber));

  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayVerseReferenceItem
 *****************************************************************************/
TextDisplayVerseReferenceItem::~TextDisplayVerseReferenceItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayVerseReferenceItem::initialize()
{
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayVerseReferenceItem::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayVerseReferenceItem::mousePressEvent
(QMouseEvent* InEvent)
{
  Qt::KeyboardModifiers                 mods;
  Qt::MouseButton                       button;


  button = InEvent->button();
  mods = InEvent->modifiers();

  if ( mods != Qt::NoModifier ) {
    return;
  }

  if ( button != Qt::LeftButton ) {
    return;
  }

  emit SignalSelected(VerseNumber);
}
