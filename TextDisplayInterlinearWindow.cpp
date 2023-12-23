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

  setMouseTracking(true);
  LeftMargin = TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH + 5;
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
  TextDisplayInterlinearReferenceItem*        referenceItem;
  int                                   lastVerseNumber;
  int                                   startIndex;
  int                                   endIndex;
  int                                   i;
  int                                   verseNumber;
  BookInfoWord*                         word;
  QString                               wordText;
  TextDisplayInterlinearItem*                 displayItem;

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
      referenceItem = new TextDisplayInterlinearReferenceItem(verseNumber, 0, 0, this);
      ReferenceItems << referenceItem;
      connect(referenceItem, TextDisplayInterlinearReferenceItem::SignalSelected,
              this, TextDisplayInterlinearWindow::SlotReferenceSelected);
      lastVerseNumber = verseNumber;
    }
    wordText = word->GetWord();
    wordText = wordText.trimmed();
    displayItem = new TextDisplayInterlinearItem(word->GetBook(),
                                           word->GetChapter(),
                                           verseNumber,
                                           wordText, i, DisplayFont);
    displayItem->setParent(this);
    displayItem->hide();
    DisplayItems << displayItem;  
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
  TRACE_FUNCTION_START();
  height =  ArrangeItems(size().width());
  TRACE_FUNCTION_INT(height);
  TRACE_FUNCTION_END();
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
  TextDisplayInterlinearReferenceItem*        referenceItem;
  int                                   verseNumber;
  QSize                                 s;
  int                                   y;
  int                                   x;
  TextDisplayInterlinearItem*                 item;
  int                                   i;
  int                                   n;
  int                                   currentVerse;
  int                                   lineHeight;
  int                                   verticalSkip = 5;
  int                                   height = 0;

  TRACE_FUNCTION_START();
  TRACE_FUNCTION_INT(InWidth);
  x = LeftMargin;
  y = TopMargin;
  n = DisplayItems.size();
  windowWidth = InWidth;
  windowWidth -= (LeftMargin + RightMargin);

  TRACE_FUNCTION_INT(Chapter);
  TRACE_FUNCTION_INT(n);
  lineHeight = 15;
  if ( n == 0 ) {
    TRACE_FUNCTION_END();
    return 0;
  }
  item = DisplayItems[0];

  currentVerse = item->GetVerseNumber();
  TRACE_FUNCTION_INT(windowWidth);
  
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
      TRACE_FUNCTION_INT(currentVerse);
      TRACE_FUNCTION_INT(i);
      TRACE_FUNCTION_INT(y);
    }
    itemSize = item->GetSize();
    itemWidth = itemSize.width();
    if ( itemWidth + x > windowWidth ) {
      y += lineHeight;
      x = LeftMargin;
      TRACE_FUNCTION_INT(i);
      TRACE_FUNCTION_INT(y);
    }
    item->move(x, y);
    x += (itemWidth + HorizontalSkip);
    if ( x > windowWidth ) {
      y += lineHeight;
      x = LeftMargin;
      TRACE_FUNCTION_INT(i);
      TRACE_FUNCTION_INT(y);
    }
    item->show();
  }
  height = y + lineHeight * 2;
  TRACE_FUNCTION_INT(height);
  TRACE_FUNCTION_END();
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
