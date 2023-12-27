/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearReferenceItem.cpp
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
#include "TextDisplayInterlinearReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearReferenceItem
 *****************************************************************************/
TextDisplayInterlinearReferenceItem::TextDisplayInterlinearReferenceItem
(int InVerseNumber, int InX, int InY, QWidget* InParent, int InRightToLeft) : QLabel(InParent)
{
  QPalette pal;
  DisplayFont = QFont("Arial", 10, QFont::Bold);
  DisplayColor = QColor(64, 0, 0);
  VerseNumber = InVerseNumber;
  RightToLeft = InRightToLeft;

  pal = palette();
  pal.setBrush(QPalette::WindowText, QBrush(DisplayColor));
  setPalette(pal);
  setAutoFillBackground(true);

  setFont(DisplayFont);

  setCursor(Qt::PointingHandCursor);
  move(InX, InY);
  resize(TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH, TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_HEIGHT);

  if ( RightToLeft ) {
    setAlignment(Qt::AlignLeft);
    setText(QString(":%1").arg(VerseNumber));
  } else {
    setAlignment(Qt::AlignRight);
    setText(QString("%1:").arg(VerseNumber));
  }
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearReferenceItem
 *****************************************************************************/
TextDisplayInterlinearReferenceItem::~TextDisplayInterlinearReferenceItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearReferenceItem::initialize()
{
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearReferenceItem::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayInterlinearReferenceItem::mousePressEvent
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

/*****************************************************************************!
 * Function : GetVerseNumber
 *****************************************************************************/
int
TextDisplayInterlinearReferenceItem::GetVerseNumber
()
{
  return VerseNumber; 
}
