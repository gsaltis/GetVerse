/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWord.cpp
 * DATE         : December 30 2023
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
#include "StrongsReferenceDisplayWord.h"
#include "BookInfo.h"

/*****************************************************************************!
 * Function : StrongsReferenceDisplayWord
 *****************************************************************************/
StrongsReferenceDisplayWord::StrongsReferenceDisplayWord
() : QLabel()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceDisplayWord
 *****************************************************************************/
StrongsReferenceDisplayWord::~StrongsReferenceDisplayWord
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceDisplayWord::initialize()
{
  setWordWrap(true);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceDisplayWord::SlotVerseReferenceClear(void)
{
  setText("");
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceDisplayWord::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  QString                               verseText;
  
  verseText = BookInfo::GetVerseText(InBookNumber, InChapterNumber, InVerseNumber);
  setText(verseText);
}
