/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceWindow.cpp
 * DATE         : November 15 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Lodal Headers
 *****************************************************************************/
#include "TextDisplaySentenceWindow.h"
#include "Trace.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceWindow
 *****************************************************************************/
TextDisplaySentenceWindow::TextDisplaySentenceWindow
(QWidget* InWidget)  : QWidget(InWidget)
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplaySentenceWindow 
 *****************************************************************************/
TextDisplaySentenceWindow::~TextDisplaySentenceWindow
()
{

}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
TextDisplaySentenceWindow::Initialize
()
{
  QPalette                              pal;

  bookInfo = NULL;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 224)));
  setPalette(pal);
  setAutoFillBackground(true);
  displayFont = MainSystemConfig->GetWordItemFont();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplaySentenceWindow::resizeEvent
(QResizeEvent* )
{
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextDisplaySentenceWindow::paintEvent
(QPaintEvent*)
{
  QPainter                      painter(this);

  for ( auto item : displayItems ) {
    item->Draw(&painter);
  }
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplaySentenceWindow::mousePressEvent
(QMouseEvent*)
{

}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplaySentenceWindow::mouseMoveEvent
(QMouseEvent*)
{

}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplaySentenceWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  leftMargin            = 10;
  rightMargin           = 10;
  interWordSkip         = 5;
  sentenceInterLineSkip = 3;
  bottomMargin          = 15;
  topMargin             = 15;
  currentChapter        = 1;
  bookInfo              = InBookInfo;

  ClearDisplayItems();
  CreateDisplayItems();
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplaySentenceWindow::SlotChapterChanged
(int InCurrentChapter)
{
  currentChapter = InCurrentChapter;
  ClearDisplayItems();
  CreateDisplayItems();
}

/*****************************************************************************!
 * Function : CreateDisplayItems
 *****************************************************************************/
void
TextDisplaySentenceWindow::CreateDisplayItems
()
{
  int                                   startIndex;
  int                                   endIndex;
  int                                   i;
  BookInfoWord*                         word;
  QString                               wordText;
  TextDisplayWordItem*                  displayItem;

  ClearDisplayItems();
  if ( NULL == bookInfo ) {
    return;
  }
  bookInfo->GetChapterWordIndices(currentChapter, startIndex, endIndex);
  for ( i = startIndex ; i <= endIndex ; i++ ) {
    word = bookInfo->GetWordByIndex(i);
    wordText = word->GetWord();
    displayItem = new TextDisplayWordItem(word->GetBook(),
                                          word->GetChapter(),
                                          word->GetVerse(),
                                          wordText, i);
    displayItem->SetFont(displayFont);
    displayItems << displayItem;  
  }
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : ClearDisplayItems
 *****************************************************************************/
void
TextDisplaySentenceWindow::ClearDisplayItems
()
{
  while ( !displayItems.isEmpty() ) {
    TextDisplayWordItem*                item;
    item = displayItems.first();
    displayItems.pop_front();
    delete item;
  } 
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
int
TextDisplaySentenceWindow::ArrangeItems
()
{
  QString                               ending;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   k;
  QSize                                 s;
  int                                   windowHeight;
  int                                   windowWidth;
  int                                   x;
  int                                   y;
  int                                   i;
  int                                   n;
  TextDisplayWordItem*                  item;
  
  x             = leftMargin;
  y             = topMargin;
  windowHeight  = 0;
  windowWidth   = size().width() - (leftMargin + rightMargin);
  
  n = displayItems.size();
  for ( i = 0 ; i < n ; i++ ) {
    item = displayItems[i];
    s = item->GetSize();
    itemWidth = s.width();
    itemHeight = s.height();
    itemText = item->GetText();
    ending = itemText.right(1);

    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }

    if ( itemWidth + x >= windowWidth ) {
      x = leftMargin;
      y += itemHeight;
      windowHeight = y + itemHeight;
    }
    item->SetLocation(QPoint(x, y));
    x += s.width() + interWordSkip;
    if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
      k = itemText.length() - 2;
      ending = itemText.sliced(k, 1);
    }
    if ( ending == "." || ending == "?" || ending == "!" ) {
      y += itemHeight + sentenceInterLineSkip;
      x = leftMargin;
      windowHeight = y + itemHeight;
    }
  }
  windowHeight += bottomMargin;
  return windowHeight;
}

