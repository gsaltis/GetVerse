/*****************************************************************************
 * FILE NAME    : StrongsReferenceVerseItem.cpp
 * DATE         : December 28 2023
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
#include "StrongsReferenceVerseItem.h"
#include "Common.h"

/*****************************************************************************!
 * Function : StrongsReferenceVerseItem
 *****************************************************************************/
StrongsReferenceVerseItem::StrongsReferenceVerseItem
(int InBookNumber, int InChapterNumber, int InVerseNumber) : QTableWidgetItem()
{
  QString                               text;
  BookNumber = InBookNumber;
  ChapterNumber = InChapterNumber;
  VerseNumber = InVerseNumber;
  bookInfo = MainBookInfo->FindBookByIndex(BookNumber);

  text = QString("%1 %2:%3").arg(bookInfo->GetName()).arg(ChapterNumber).arg(VerseNumber);
  setText(text);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceVerseItem
 *****************************************************************************/
StrongsReferenceVerseItem::~StrongsReferenceVerseItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceVerseItem::initialize()
{
}

/*****************************************************************************!
 * Function : GetReference
 *****************************************************************************/
void
StrongsReferenceVerseItem::GetReference
(int &InBookNumber, int &InChapterNumber, int &InVerseNumber)
{
  InBookNumber = BookNumber;
  InChapterNumber = ChapterNumber;
  InVerseNumber = VerseNumber;
}
