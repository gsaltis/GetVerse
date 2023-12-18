/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceWindow.cpp
 * DATE         : November 15 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Lodal Headers
 *****************************************************************************/
#include "TextDisplaySentenceWindow.h"
#include "Common.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceWindow
 *****************************************************************************/
TextDisplaySentenceWindow::TextDisplaySentenceWindow
()  : QWidget()
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
  QString s = displayFont.family();
  maxChapters = 0;
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
  interWordSkip         = 3;
  sentenceInterLineSkip = 3;
  bottomMargin          = 15;
  topMargin             = 15;
  currentChapter        = 1;
  bookInfo              = InBookInfo;
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplaySentenceWindow::SlotChapterChanged
(int InCurrentChapter)
{
  currentChapter = InCurrentChapter;
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
  TextDisplaySentenceItem*              displayItem;

  ClearDisplayItems();
  if ( NULL == bookInfo ) {
    return;
  }

  maxChapters = bookInfo->chapters;
  bookInfo->GetChapterWordIndices(currentChapter, startIndex, endIndex);
  for ( i = startIndex ; i <= endIndex ; i++ ) {
    word = bookInfo->GetWordByIndex(i);
    wordText = word->GetWord();
    displayItem = new TextDisplaySentenceItem(word->GetBook(),
                                              word->GetChapter(),
                                              word->GetVerse(),
                                              wordText, i);
    displayItem->setParent(this);
    displayItem->hide();
    displayItem->SetFont(displayFont);
    displayItems << displayItem;  
  }
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
    TextDisplaySentenceItem*            item;
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
(int InWidth)
{
  QString                               ending;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   k;
  QSize                                 s;
  int                                   windowWidth;
  int                                   x;
  int                                   y;
  int                                   i;
  int                                   n;
  TextDisplaySentenceItem*              item;
  int                                   sentenceCount;

  x             = leftMargin;
  y             = topMargin;
  windowHeight  = 0;
  windowWidth   = InWidth - (leftMargin + rightMargin);
  sentenceCount = 0;
  n = displayItems.size();
  for ( i = 0 ; i < n ; i++ ) {
    item = displayItems[i];
    s = item->size();
    itemWidth = s.width();
    itemHeight = s.height();
    itemText = item->GetText();
    ending = itemText.right(1);

    if ( itemWidth + x >= windowWidth ) {
      x = leftMargin;
      y += itemHeight;
      windowHeight = y + itemHeight;
    }
    item->move(QPoint(x, y));
    x += s.width() + interWordSkip;
    if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
      k = itemText.length() - 2;
      ending = itemText.sliced(k, 1);
    }
    if ( ending == "." || ending == "?" || ending == "!" ) {
      sentenceCount++;
      y += itemHeight + sentenceInterLineSkip;
      x = leftMargin;
      windowHeight = y + itemHeight;
    }
    item->show();
  }
  windowHeight += bottomMargin;
  emit SignalSentenceCountChanged(sentenceCount);
  return windowHeight;
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplaySentenceWindow::keyPressEvent
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
TextDisplaySentenceWindow::KeyPress
(int InKey, Qt::KeyboardModifiers InModifiers)
{
  int                                   newChapter;

  if ( maxChapters == 0 ) {
    return false;
  }

  if ( InModifiers != Qt::NoModifier ) {
    return false;
  }

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
    emit SignalSetStartupBookmarkInfo(bookInfo, currentChapter);
    return true;
  }
  
  if ( InKey == Qt::Key_Left ) {
    if ( currentChapter <= 1 ) {
      return true;
    }
    newChapter = currentChapter - 1;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  if ( InKey == Qt::Key_Right ) {
    if ( currentChapter >= maxChapters ) {
      return true;
    }

    if( currentChapter >= maxChapters ) {
      return true;
    }
    newChapter = currentChapter+1;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  return false;
}

/*****************************************************************************!
 * Function : GetWindowHeight
 *****************************************************************************/
int
TextDisplaySentenceWindow::GetWindowHeight
()
{
  return windowHeight;
}
