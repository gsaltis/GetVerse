/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindow.cpp
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QThread>
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewWindow.h"
#include "Common.h"
#include "Trace.h"
#include "TextDisplayViewWindowItem.h"
#include "TextDisplayViewWindowReferenceItem.h"
#include "TextDisplayReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayViewWindow
 *****************************************************************************/
TextDisplayViewWindow::TextDisplayViewWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setFont(displayFont);
  setMouseTracking(true);
  lastSelectedItem = NULL;
}

/*****************************************************************************!
 * Function : ~TextDisplayViewWindow
 *****************************************************************************/
TextDisplayViewWindow::~TextDisplayViewWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewWindow::initialize()
{
  InterLineSkip = 3;
  InterParagraphSkip = 10;
  InterWordSkip = 4;
  rightMargin   = 30;
  leftMargin    = 10;
  bottomMargin  = 10;
  topMargin     = 10;
  tableSize     = QSize();
  sentenceIndent = 30;
  mode = ReferenceMode;
  displayFont = QFont("Arial", 11, QFont::Normal);
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewWindow::InitializeSubWindows()
{
  
}
/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QSize                                 s;
  emit SignalShowProgressBar();
  bookInfo = InBookInfo;
  verseCount = GetVerseCount();
  emit SignalSetProgressBar(0, verseCount);
  GetMaxReferenceWidth();
  SetBook();
  ArrangeItems();
  ComputeSize();
  // resize(tableSize);
  repaint();
  s = size();
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
void
TextDisplayViewWindow::ArrangeItems
()
{
  int                                   height;
  int                                   x;
  int                                   y;
  int                                   windowWidth;
  
  y             = topMargin;
  x             = leftMargin;  
  height        = 0;
  windowWidth   = tableWidth - (leftMargin + rightMargin);
  TRACE_FUNCTION_INT(windowWidth);
  TRACE_FUNCTION_INT(tableWidth);
  switch (mode) {
    case NoneMode : {
      break;
    }
    case ReferenceMode : {
      height = ArrangeItemsReference(x, y, windowWidth);
      break;
    }
    case BlockMode : {
      height = ArrangeItemsBlock(x, y, windowWidth);
      break;
    }
    case SentenceMode : {
      height = ArrangeItemsSentence(x, y, windowWidth);
      break;
    }
  }
  windowSize = QSize(tableWidth, height);
  resize(windowSize);
}

/*****************************************************************************!
 * Function : ArrangeItemsReference
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsReference
(int InX, int InY, int InWindowWidth)
{
  QSize                                 s;
  int                                   itemWidth;
  int                                   itemHeight;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  bool                                  isFirst;

  x             = InX;
  y             = InY;
  windowHeight  = 0;
  
  do {
    isFirst = true;
    for ( auto item : textItems ) {
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      
      if ( !isFirst && item->GetType() == TextDisplayItem::ReferenceType ) {
        x = leftMargin;
        y += InterLineSkip + itemHeight;
        windowHeight = y + itemHeight;
      }
      if ( itemWidth + x >= InWindowWidth ) {
        x = leftMargin + referenceWidth + InterWordSkip;
        y += InterLineSkip + itemHeight;
        windowHeight = y + itemHeight;
      }
      isFirst = false;
      item->SetLocation(QPoint(x, y));
      x += s.width() + InterWordSkip;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : ArrangeItemsBlock
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsBlock
(int InX, int InY, int InWindowWidth)
{
  TextDisplayReferenceItem*             referenceItem;
  bool                                  breakAfter;
  int                                   formatting;
  int                                   verse;
  int                                   chapter;
  int                                   book;
  QString                               ending;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  QSize                                 s;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  
  x             = InX;
  y             = InY;
  windowHeight  = 0;

  breakAfter = false;
  do {
    for ( auto item : textItems ) {
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      itemText = item->GetText();
      ending = itemText.right(1);
      
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        if ( breakAfter ) {
          x = leftMargin;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          breakAfter = false;
        }
        referenceItem = (TextDisplayReferenceItem*)item;
        verse = referenceItem->GetVerse();
        chapter = referenceItem->GetChapter();
        book = bookInfo->index;
        formatting = GetFormattingByReference(book, chapter, verse);
        if ( formatting == 1 ) {
          breakAfter = true;
          continue;
        }
        if ( formatting == 2 ) {
          x = leftMargin;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          continue;
        }
        continue;
      }
      if ( itemWidth + x >= InWindowWidth ) {
        x = leftMargin;
        y += itemHeight;
        windowHeight = y + itemHeight;
      }
      item->SetLocation(QPoint(x, y));
      x += s.width() + InterWordSkip;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : ArrangeItemsSentence
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsSentence
(int InX, int InY, int InWindowWidth)
{
  QString                               ending;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   k;
  QSize                                 s;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  
  x             = InX;
  y             = InY;
  windowHeight  = 0;
  
  do {
    for ( auto item : textItems ) {
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      itemText = item->GetText();
      ending = itemText.right(1);
      
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        continue;
      }
      if ( itemWidth + x >= InWindowWidth ) {
        x = leftMargin + sentenceIndent;
        y += itemHeight;
        windowHeight = y + itemHeight;
      }
      item->SetLocation(QPoint(x, y));
      x += s.width() + InterWordSkip;
      if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
        k = itemText.length() - 2;
        ending = itemText.sliced(k, 1);
      }
      if ( ending == "." || ending == "?" || ending == "!" ) {
        tmpSentenceCount ++;
        y += itemHeight + InterLineSkip * 2;
        x = leftMargin;
        windowHeight = y + itemHeight;
      }
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : GetMaxReferenceWidth
 *****************************************************************************/
void
TextDisplayViewWindow::GetMaxReferenceWidth
()
{
  QSize                                 s2;
  QString                               reference;
  int                                   verse;
  int                                   chapter;
  int                                   width;
  int                                   retryCount;
  sqlite3_stmt*                         sqlstmt;
  int                                   n;
  QString                               query;
  QFontMetrics                          fm(displayFont);

  referenceWidth = 0;
  
  query = 
     QString("SELECT chapter, verse FROM Verses WHERE book is %1;\n")
    .arg(bookInfo->index);

  n = sqlite3_prepare_v2(MainDatabase,
                         query.toStdString().c_str(),
                         query.length(),
                         &sqlstmt,
                         NULL);
  if ( n != SQLITE_OK ) {
    return;
  }

  retryCount = 0;
  do {
    n = sqlite3_step(sqlstmt);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      chapter = sqlite3_column_int(sqlstmt, 0);
      verse = sqlite3_column_int(sqlstmt, 1);
      reference = QString("%2:%3").arg(chapter).arg(verse);
      s2 = fm.size(0, reference);
      width = s2.width();
      if ( referenceWidth < width ) {
        referenceWidth = width;
      }
    }
  } while (true);
  sqlite3_finalize(sqlstmt);
}
  
/*****************************************************************************!
 * Function : SetBook
 *****************************************************************************/
void
TextDisplayViewWindow::SetBook
()
{
  QString                               columnName;
  int                                   n;
  QString                               sqlstmt;

  tmpVerseCount = 0;
  wordCount = 0;
  ClearText();
  sqlstmt = QString("SELECT * from Verses where book is %1;\n").arg(bookInfo->index);
  tmpVerseCount = 0;
  tmpSentenceCount = 0;
  n = sqlite3_exec(MainDatabase, sqlstmt.toStdString().c_str(), SetBookCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, sqlstmt.toStdString().c_str(),
            sqlite3_errstr(n));
    return;
  }

  emit SignalWordCountChanged(wordCount);
}

/*****************************************************************************!
 * Function : SetBookCB
 *****************************************************************************/
int
TextDisplayViewWindow::SetBookCB
(void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   chapter = 0;
  int                                   verse = 0;
  QString                               columnValue;
  QString                               columnName;
  QString                               verseText;
  QString                               reference;
  QString                               s;
  TextDisplayViewWindow*                window;

  window = (TextDisplayViewWindow*)InThisPointer;
  
  for ( int i = 0 ; i < InColumnCount ; i++ ) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "key" ) {
      reference = columnValue;
      continue;
    }

    if ( columnName == "chapter" ) {
      chapter = columnValue.toInt();
      continue;
    }
    if ( columnName == "verse" ) {
      verse = columnValue.toInt();
      continue;
    }
    if ( columnName == "text" ) {
      verseText = columnValue;
      continue;
    }
  }

  window->AddLineText(chapter, verse, verseText);
  return 0;
}

/*****************************************************************************!
 * Function : AddLineText
 *****************************************************************************/
void
TextDisplayViewWindow::AddLineText
(int InChapter, int InVerse, QString InVerseText)
{
  int                                   i;
  int                                   n;
  QStringList                           words;
  TextDisplayItem*                      item;
  TextDisplayReferenceItem*             refItem;
  QString                               referenceText;

  refItem = new TextDisplayReferenceItem(bookInfo->index,
                                         bookInfo->GetCapitalizedBookName(),
                                         InChapter, InVerse);
  refItem->SetFont(displayFont);
  refItem->SetSize(QSize(referenceWidth, refItem->GetSize().height()));
  textItems.push_back(refItem);
  words = InVerseText.split(" ");
  n = words.size();

  for ( i = 0; i < n; i++ ) {
    item = new TextDisplayItem(bookInfo->index, InChapter, InVerse, words[i]);
    item->SetFont(displayFont);
    textItems.push_back(item);
    tmpVerseCount++;
    emit SignalUpdateProgressBar(tmpVerseCount);
    QCoreApplication::processEvents();
  }    
}

/*****************************************************************************!
 * Function : ClearText
 *****************************************************************************/
void
TextDisplayViewWindow::ClearText
()
{
  while ( QWidget* w = findChild<QWidget*>() ) {
    delete w;
  }
  textItems.clear();
  textY = topMargin;
}

/*****************************************************************************!
 * Function : ComputeSize
 *****************************************************************************/
QSize
TextDisplayViewWindow::ComputeSize
()
{
  int                                   height;
  int                                   h1;
  QPoint                                p;
  QSize                                 s;

  height = 0;
  for ( auto item : textItems ) {
    s = item->GetSize();
    p = item->GetLocation();

    h1 = s.height() + p.y();
    if ( height < h1 ) {
      height = h1;
    }
  }
  height += (topMargin  + bottomMargin);
  return QSize(size().width(), height);
}

/*****************************************************************************!
 * Function : GetTableHeight
 *****************************************************************************/
int
TextDisplayViewWindow::GetTableHeight
()
{
  return windowSize.height();
}

/*****************************************************************************!
 * Function : GetVerseCount
 *****************************************************************************/
int
TextDisplayViewWindow::GetVerseCount
()
{
  int                                   verseCount;
  sqlite3_stmt*                         sqlstmt;
  int                                   n;
  int                                   len;
  QString                               query;
  int                                   retryCount = 0;
  
  query = QString("SELECT COUNT(*) FROM Verses WHERE book is %1;\n").arg(bookInfo->index);
  len = query.length();
  
  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(), len, &sqlstmt, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s sqlite3_prepare_v2()\n%s\n%s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return 0;
  }
  retryCount = 0;
  verseCount = 0;
  do {
    n = sqlite3_step(sqlstmt);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      verseCount = sqlite3_column_int(sqlstmt, 0);
    }
  } while (true);

  sqlite3_finalize(sqlstmt);
  return verseCount;
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetSentenceMode(void)
{
  mode = SentenceMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetBlockMode(void)
{
  mode = BlockMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetReferenceMode(void)
{
  mode = ReferenceMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : GetFormattingByReference
 *****************************************************************************/
int
TextDisplayViewWindow::GetFormattingByReference
(int InBook, int InChapter, int InVerse)
{
  int                                   type;
  int                                   n;
  int                                   retryCount;
  sqlite3_stmt*                         statement;
  QString                               query;
  
  query = QString("SELECT type FROM Formatting WHERE book is %1 and chapter is %2 and verse is %3;\n").
    arg(InBook).arg(InChapter).arg(InVerse);

  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(),
                         query.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "sqlite3_prepare_v2() %s failed\n  %s\n  %s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return 0;
  }
  type = 0;
  retryCount = 0;
  do {
    n = sqlite3_step(statement);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      type = sqlite3_column_int(statement, 0);
      break;
    }
  } while (true);
  sqlite3_finalize(statement);
  return type;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 s;

  s = InEvent->size();
  tableWidth = s.width();
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextDisplayViewWindow::paintEvent
(QPaintEvent* InEvent)
{
  QPainter                              painter(this);
  QRect                                 rect = InEvent->rect();

  switch (mode) {
    case ReferenceMode : {
      PaintReferenceMode(&painter, rect);
      break;
    }
    case SentenceMode : {
      PaintSentenceMode(&painter, rect);
      break;
    }
    case BlockMode : {
      PaintBlockMode(&painter, rect);
      break;
    }
    case NoneMode : {
      break;
    }
  }
  painter.end();
}

/*****************************************************************************!
 * Function : PaintReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintReferenceMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;

  
  for ( auto item : textItems ) {
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        item->Draw(InPainter);
      }
    }
  } while (false);
}


/*****************************************************************************!
 * Function : PaintSentenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintSentenceMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;
  
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        item->Draw(InPainter);
      }
    }
  } while (false);
}

/*****************************************************************************!
 * Function : PaintBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintBlockMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;
  
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        item->Draw(InPainter);
      }
    }
  } while (false);
}

/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplayViewWindow::mouseMoveEvent
(QMouseEvent* InEvent)
{
  QString                               text;
  QPoint                                p = InEvent->position().toPoint();

  if ( lastSelectedItem && lastSelectedItem->Contains(p) ) {
    return;
  }
  lastSelectedItem = NULL;
  for ( auto item : textItems ) {
    if ( item->Contains(p) ) {
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        continue;
      }
      text = item->GetText();
      if ( item != lastSelectedItem ) {
        lastSelectedItem = item;
        break;
      }
    }
  }
  repaint();
}

/*****************************************************************************!
 * Function : SlotVerticalScrolled
 *****************************************************************************/
void
TextDisplayViewWindow::SlotVerticalScrolled(void)
{
  lastSelectedItem = NULL;
  repaint();
}
