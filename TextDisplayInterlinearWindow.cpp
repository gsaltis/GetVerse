/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearWindow.cpp
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayInterlinearWindow.h"
#include "BookInfoWord.h"
#include "TextDisplayInterlinearReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearWindow
 *****************************************************************************/
TextDisplayInterlinearWindow::TextDisplayInterlinearWindow
() : QWidget()
{
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearWindow
 *****************************************************************************/
TextDisplayInterlinearWindow::~TextDisplayInterlinearWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearWindow::initialize()
{
  QPalette                              pal;

  Book = NULL;
  Chapter = 0;
  interlinearChapter = NULL;
  
  setMouseTracking(true);
  LeftMargin = TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH + 5;
  LeftIndent = 40;
  RightMargin = 30;
  TopMargin = 20;
  HorizontalSkip = 10;
  VerticalSkip = 20;
  VerticalSkipSmall = VerticalSkip / 2;
  DisplayColor = QColor(32, 32, 32);
  ReferenceColor = QColor(32, 0, 0);
  BackgroundColor = QColor(255, 255, 255);
  
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(BackgroundColor));
  setPalette(pal);
  setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearWindow::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayInterlinearWindow::SlotBookSelected
(BookInfo* InBook)
{
  Book = InBook;
  maxChapters = Book->GetChapterCount();
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayInterlinearWindow::SlotChapterSelected
(int InChapter)
{
  Chapter = InChapter;
  if ( interlinearChapter ) {
    delete interlinearChapter;
  }
  if ( NULL == Book ) {
    return;
  }
  
  interlinearChapter = new InterlinearChapter(Book->GetIndex(), Chapter);
  interlinearChapter->Read();
  interlinearChapter->ReadVerses();
  ClearDisplayItems();
  CreateDisplayItems();
}

/*****************************************************************************!
 * Function : CreateDisplayItems
 *****************************************************************************/
void
TextDisplayInterlinearWindow::CreateDisplayItems
()
{
  int                                   rightToLeft;
  int                                   verseNumber;
  int                                   j;
  int                                   k;
  int                                   wordCount;
  InterlinearVerse*                     verse;
  int                                   verseCount;
  TextDisplayInterlinearReferenceItem*  referenceItem;
  int                                   i;
  InterlinearWord*                      word;
  TextDisplayInterlinearItem*           displayItem;

  ClearDisplayItems();
  if ( interlinearChapter == NULL ) {
    return;
  }


  verseCount = interlinearChapter->GetVerseCount();
  if ( verseCount == 0 ) {
    return;
  }
  rightToLeft = Book->GetRightToLeft();
  k = 0;
  for (i = 0; i < verseCount; i++) {
    verse = interlinearChapter->GetVerseByIndex(i);
    verseNumber = verse->GetVerseNumber();
    referenceItem = new TextDisplayInterlinearReferenceItem(verseNumber, 0, 0, this, rightToLeft);
    ReferenceItems << referenceItem;
    wordCount = verse->GetWordCount();
    for (j = 0; j < wordCount; j++) {
      word = verse->GetWordByIndex(j);
      displayItem = new TextDisplayInterlinearItem(word, k, this, rightToLeft);
      connect(displayItem, TextDisplayInterlinearItem::SignalSelectStrongsWord, this, TextDisplayInterlinearWindow::SlotSelectStrongsWord);
      DisplayItems << displayItem;
      k++;
    }
  }
  ArrangeItems();
}

/*****************************************************************************!
 * Function : ClearDisplayItems
 *****************************************************************************/
void
TextDisplayInterlinearWindow::ClearDisplayItems
()
{
  while ( !DisplayItems.isEmpty() ) {
    TextDisplayInterlinearItem*               item;
    item = DisplayItems.first();
    DisplayItems.pop_front();
    delete item;
  } 
  while ( !ReferenceItems.isEmpty() ) {
    TextDisplayInterlinearReferenceItem*      item;
    item = ReferenceItems.first();
    ReferenceItems.pop_front();
    delete item;
  } 
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
int
TextDisplayInterlinearWindow::ArrangeItems
()
{
  int                                   height;
  height =  ArrangeItems(size().width());
  return height;
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
int
TextDisplayInterlinearWindow::ArrangeItems
(int InWidth)
{
  QSize                                 itemSize;
  int                                   itemWidth;
  int                                   windowWidth;
  TextDisplayInterlinearReferenceItem*  referenceItem;
  int                                   verseNumber;
  QSize                                 s;
  int                                   y;
  int                                   x;
  TextDisplayInterlinearItem*           item;
  int                                   i;
  int                                   n;
  int                                   currentVerse;
  int                                   lineHeight;
  int                                   height = 0;

  if ( Book == NULL ) {
    return 0 ;
  }
  if ( Book->GetRightToLeft() ) {
    return ArrangeItemsRightToLeft(size().width());
  }
  
  x = LeftMargin;
  y = TopMargin;
  n = DisplayItems.size();
  windowWidth = InWidth;
  windowWidth -= (LeftMargin + RightMargin);

  lineHeight = 0;
  if ( n == 0 ) {
    return 0;
  }
  item = DisplayItems[0];

  currentVerse = item->GetVerseNumber();
  x = 0;
  referenceItem = FindReferenceByVerseNumber(currentVerse);
  referenceItem->move(x, y);
  referenceItem->show();
  x = LeftMargin;

  lineHeight = DisplayItems[0]->GetSize().height();
  //!
  for (i = 0; i < n; i++) {
    item = DisplayItems[i];
    s = item->GetSize();
    verseNumber = item->GetVerseNumber();
    if ( currentVerse != verseNumber ) {
      x = 0;
      y += (lineHeight + VerticalSkip);
      currentVerse = verseNumber;
      referenceItem = FindReferenceByVerseNumber(currentVerse);
      referenceItem->move(x, y);
      referenceItem->show();
      x = LeftMargin;
    }
    itemSize = item->GetSize();
    itemWidth = itemSize.width();
    if ( itemWidth + x > windowWidth ) {
      y += lineHeight + VerticalSkipSmall;
      x = LeftMargin;
    }
    item->move(x, y);
    x += (itemWidth + HorizontalSkip);
    if ( x > windowWidth ) {
      y += lineHeight + VerticalSkipSmall;
      x = LeftMargin;
    }
    item->show();
  }
  height = y + lineHeight * 2;
  return height;
}

/*****************************************************************************!
 * Function : ArrangeItemsRightToLeft
 *****************************************************************************/
int
TextDisplayInterlinearWindow::ArrangeItemsRightToLeft
(int InWidth)
{
  int                                   referenceX;
  int                                   verseX;
  QSize                                 itemSize;
  int                                   itemWidth;
  TextDisplayInterlinearReferenceItem*  referenceItem;
  int                                   verseNumber;
  QSize                                 s;
  int                                   y;
  int                                   x;
  TextDisplayInterlinearItem*           item;
  int                                   i;
  int                                   n;
  int                                   currentVerse;
  int                                   lineHeight;
  int                                   height = 0;


  n = DisplayItems.size();
  if ( n == 0 ) {
    return 0;
  }

  //!
  verseX = InWidth - (TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH + 5);
  referenceX = InWidth - TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH;
  y = TopMargin;
  
  lineHeight = DisplayItems[0]->GetSize().height();

  //!
  item = DisplayItems[0];
  currentVerse = item->GetVerseNumber();
  referenceItem = FindReferenceByVerseNumber(currentVerse);
  referenceItem->move(referenceX, y);
  referenceItem->show();
  x = verseX;

  //!
  for (i = 0; i < n; i++) {
    item = DisplayItems[i];
    s = item->GetSize();
    verseNumber = item->GetVerseNumber();
    if ( currentVerse != verseNumber ) {
      y += (lineHeight + VerticalSkip);
      currentVerse = verseNumber;
      referenceItem = FindReferenceByVerseNumber(currentVerse);
      referenceItem->move(referenceX, y);
      referenceItem->show();
      x = verseX;
    }
    itemSize = item->GetSize();
    itemWidth = itemSize.width();
    if ( itemWidth + x < LeftMargin ) {
      y += lineHeight;
      x = verseX;
    }
    if ( x - itemWidth < LeftMargin ) {
      y += lineHeight + VerticalSkipSmall;
      x = verseX;
    }
    x -= itemWidth;
    item->move(x, y);
    x -= HorizontalSkip;
    item->show();
  }
  height = y + lineHeight * 2;
  return height;
}

/*****************************************************************************!
 * Function : SlotReferenceSelected
 *****************************************************************************/
void
TextDisplayInterlinearWindow::SlotReferenceSelected
(int InVerseNumber)
{
  (void)InVerseNumber;
}

/*****************************************************************************!
 * Function : FindReferenceByInterlinearNumber
 *****************************************************************************/
TextDisplayInterlinearReferenceItem*
TextDisplayInterlinearWindow::FindReferenceByVerseNumber
(int InVerseNumber)
{
  for ( auto ref : ReferenceItems ) {
    if ( InVerseNumber == ref->GetVerseNumber() ) {
      return ref;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplayInterlinearWindow::keyPressEvent
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
 * Function : KeyPress
 *****************************************************************************/
bool
TextDisplayInterlinearWindow::KeyPress
(int InKey, Qt::KeyboardModifiers InModifiers)
{
  int                                   newChapter;

  if ( maxChapters == 0 ) {
    return false;
  }

  if ( InModifiers != Qt::NoModifier ) {
    return false;
  }
  (void)InKey;

  if ( InKey == Qt::Key_I ) {
    emit SignalWindowChange(5);
    return true;
  }
  
  if ( InKey == Qt::Key_B ) {
    emit SignalWindowChange(2);
    return true;
  }
  
  if ( InKey == Qt::Key_E ) {
    emit SignalWindowChange(3);
    return true;
  }
  
  if ( InKey == Qt::Key_S ) {
    emit SignalWindowChange(4);
    return true;
  }

  if ( InKey == Qt::Key_V ) {
    emit SignalWindowChange(1);
    return true;
  }

  if ( InKey == Qt::Key_0 ) {
    emit SignalSetStartupBookmarkInfo(Book, Chapter);
    return true;
  }
  
  if ( InKey == Qt::Key_Left ) {
    if ( Chapter <= 1 ) {
      return true;
    }
    newChapter = Chapter - 1;
    SlotChapterSelected(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  if ( InKey == Qt::Key_Right ) {
    if ( Chapter >= maxChapters ) {
      return true;
    }

    if( Chapter >= maxChapters ) {
      return true;
    }
    newChapter = Chapter+1;
    SlotChapterSelected(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  return false;
}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplayInterlinearWindow::mouseMoveEvent
(QMouseEvent* )
{
  setFocus();
}

/*****************************************************************************!
 * Function : SlotSelectStrongsWord
 *****************************************************************************/
void
TextDisplayInterlinearWindow::SlotSelectStrongsWord
(QString InStrongsWord)
{
  emit SignalSelectStrongsWord(InStrongsWord);  
}
