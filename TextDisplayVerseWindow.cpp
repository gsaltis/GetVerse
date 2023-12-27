/*****************************************************************************
 * FILE NAME    : TextDisplayVerseWindow.cpp
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
#include "TextDisplayVerseWindow.h"
#include "BookInfoWord.h"
#include "TextDisplayVerseReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayVerseWindow
 *****************************************************************************/
TextDisplayVerseWindow::TextDisplayVerseWindow
() : QWidget()
{
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayVerseWindow
 *****************************************************************************/
TextDisplayVerseWindow::~TextDisplayVerseWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayVerseWindow::initialize()
{
  QPalette                              pal;

  Book = NULL;
  Chapter = 0;

  setMouseTracking(true);
  LeftMargin = TEXT_DISPLAY_VERSE_REFERENCE_ITEM_WIDTH + 5;
  LeftIndent = 40;
  RightMargin = 30;
  TopMargin = 20;
  HorizontalSkip = 3;
  
  DisplayFont = QFont("Arial", 11, QFont::Normal);
  ReferenceFont = QFont("Arial", 11, QFont::Bold);

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
TextDisplayVerseWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayVerseWindow::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayVerseWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayVerseWindow::SlotBookSelected
(BookInfo* InBook)
{
  Book = InBook;
  maxChapters = Book->GetChapterCount();
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayVerseWindow::SlotChapterSelected
(int InChapter)
{
  Chapter = InChapter;
  ClearDisplayItems();
  CreateDisplayItems();
}

/*****************************************************************************!
 * Function : CreateDisplayItems
 *****************************************************************************/
void
TextDisplayVerseWindow::CreateDisplayItems
()
{
  TextDisplayVerseReferenceItem*        referenceItem;
  int                                   lastVerseNumber;
  int                                   startIndex;
  int                                   endIndex;
  int                                   i;
  int                                   verseNumber;
  BookInfoWord*                         word;
  QString                               wordText;
  TextDisplayVerseItem*                 displayItem;

  ClearDisplayItems();
  if ( NULL == Book ) {
    return;
  }
  lastVerseNumber = 0;
  Book->GetChapterWordIndices(Chapter, startIndex, endIndex);
  for ( i = startIndex ; i <= endIndex ; i++ ) {
    word = Book->GetWordByIndex(i);
    verseNumber = word->GetVerse();
    if ( verseNumber != lastVerseNumber ) {
      referenceItem = new TextDisplayVerseReferenceItem(verseNumber, 0, 0, this);
      ReferenceItems << referenceItem;
      connect(referenceItem, TextDisplayVerseReferenceItem::SignalSelected,
              this, TextDisplayVerseWindow::SlotReferenceSelected);
      lastVerseNumber = verseNumber;
    }
    wordText = word->GetWord();
    wordText = wordText.trimmed();
    displayItem = new TextDisplayVerseItem(word->GetBook(),
                                           word->GetChapter(),
                                           verseNumber,
                                           wordText, i, DisplayFont);
    displayItem->setParent(this);
#if 0    
     displayItem->hide();
#endif     
    DisplayItems << displayItem;  
  }
  ArrangeItems();
}

/*****************************************************************************!
 * Function : ClearDisplayItems
 *****************************************************************************/
void
TextDisplayVerseWindow::ClearDisplayItems
()
{
  while ( !DisplayItems.isEmpty() ) {
    TextDisplayVerseItem*               item;
    item = DisplayItems.first();
    DisplayItems.pop_front();
    delete item;
  } 
  while ( !ReferenceItems.isEmpty() ) {
    TextDisplayVerseReferenceItem*      item;
    item = ReferenceItems.first();
    ReferenceItems.pop_front();
    delete item;
  } 
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
int
TextDisplayVerseWindow::ArrangeItems
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
TextDisplayVerseWindow::ArrangeItems
(int InWidth)
{
  QSize                                 itemSize;
  int                                   itemWidth;
  int                                   windowWidth;
  TextDisplayVerseReferenceItem*        referenceItem;
  int                                   verseNumber;
  QSize                                 s;
  int                                   y;
  int                                   x;
  TextDisplayVerseItem*                 item;
  int                                   i;
  int                                   n;
  int                                   currentVerse;
  int                                   lineHeight;
  int                                   verticalSkip = 5;
  int                                   height = 0;

  x = LeftMargin;
  y = TopMargin;
  n = DisplayItems.size();
  windowWidth = InWidth;
  windowWidth -= (LeftMargin + RightMargin);

  lineHeight = 15;
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

  //!
  for (i = 0; i < n; i++) {
    item = DisplayItems[i];
    s = item->GetSize();
    verseNumber = item->GetVerseNumber();
    if ( currentVerse != verseNumber ) {
      x = 0;
      y += (lineHeight + verticalSkip);
      currentVerse = verseNumber;
      referenceItem = FindReferenceByVerseNumber(currentVerse);
      referenceItem->move(x, y);
      referenceItem->show();
      x = LeftMargin;
    }
    itemSize = item->GetSize();
    itemWidth = itemSize.width();
    if ( itemWidth + x > windowWidth ) {
      y += lineHeight;
      x = LeftMargin;
    }
    item->move(x, y);
    x += (itemWidth + HorizontalSkip);
    if ( x > windowWidth ) {
      y += lineHeight;
      x = LeftMargin;
    }
    item->show();
  }
  height = y + lineHeight * 2;
  return height;
}

/*****************************************************************************!
 * Function : SlotReferenceSelected
 *****************************************************************************/
void
TextDisplayVerseWindow::SlotReferenceSelected
(int InVerseNumber)
{
  (void)InVerseNumber;
}

/*****************************************************************************!
 * Function : FindReferenceByVerseNumber
 *****************************************************************************/
TextDisplayVerseReferenceItem*
TextDisplayVerseWindow::FindReferenceByVerseNumber
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
TextDisplayVerseWindow::keyPressEvent
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
TextDisplayVerseWindow::KeyPress
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
TextDisplayVerseWindow::mouseMoveEvent
(QMouseEvent* )
{
  setFocus();
}
