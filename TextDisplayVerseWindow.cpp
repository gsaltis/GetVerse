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

  LeftMargin = 20;
  LeftIndent = 60;
  RightMargin = 30;
  TopMargin = 10;
  
  DisplayFont = QFont("Arial", 10, QFont::Normal);
  ReferenceFont = QFont("Arial", 10, QFont::Bold);

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
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayVerseWindow::resizeEvent
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
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayVerseWindow::SlotBookSelected
(BookInfo* InBook)
{
  Book = InBook;
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayVerseWindow::SlotChapterSelected
(int InChapter)
{
  Chapter = InChapter;
  CreateDisplayItems();
}

/*****************************************************************************!
 * Function : CreateDisplayItems
 *****************************************************************************/
void
TextDisplayVerseWindow::CreateDisplayItems
()
{
  int                                   startIndex;
  int                                   endIndex;
  int                                   i;
  BookInfoWord*                         word;
  QString                               wordText;
  TextDisplayVerseItem*                 displayItem;

  ClearDisplayItems();
  if ( NULL == Book ) {
    return;
  }

  Book->GetChapterWordIndices(Chapter, startIndex, endIndex);
  for ( i = startIndex ; i <= endIndex ; i++ ) {
    word = Book->GetWordByIndex(i);
    wordText = word->GetWord();
    displayItem = new TextDisplayVerseItem(word->GetBook(),
                                           word->GetChapter(),
                                           word->GetVerse(),
                                           wordText, i);
    displayItem->setParent(this);
    displayItem->hide();
    displayItem->SetFont(DisplayFont);
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
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
void
TextDisplayVerseWindow::ArrangeItems(void)
{
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
  
  x = LeftMargin;
  y = TopMargin;
  n = DisplayItems.size();

  lineHeight = 15;
  if ( n == 0 ) {
    return;
  }
  item = DisplayItems[0];

  currentVerse = item->GetVerseNumber();
  
  x = 0;
  referenceItem = new TextDisplayVerseReferenceItem(currentVerse, x, y, this);
  connect(referenceItem, TextDisplayVerseReferenceItem::SignalSelected,
          this, TextDisplayVerseWindow::SlotReferenceSelected);
  x = LeftMargin;
  
  for (i = 0; i < n; i++) {
    item = DisplayItems[i];
    s = item->GetSize();
    verseNumber = item->GetVerseNumber();
    if ( currentVerse != verseNumber ) {
      x = 0;
      y += (lineHeight + verticalSkip);
      currentVerse = verseNumber;
      referenceItem = new TextDisplayVerseReferenceItem(verseNumber, x, y, this);
      connect(referenceItem, TextDisplayVerseReferenceItem::SignalSelected,
              this, TextDisplayVerseWindow::SlotReferenceSelected);
      x = LeftMargin;
    }
  }
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
