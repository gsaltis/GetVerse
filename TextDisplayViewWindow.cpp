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
#include "TextDisplayWordItem.h"
#include "SQLStatement.h"

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
  EditViewReferenceIndent       = 40;
  InterLineSkip                 = 3;
  InterParagraphSkip            = 10;
  InterWordSkip                 = 4;
  bottomMargin                  = 10;
  leftMargin                    = 10;
  rightMargin                   = 30;
  sentenceIndent                = 30;
  tableSize                     = QSize();
  topMargin                     = 10;
  DotsPerInchX                  = (int)screen()->logicalDotsPerInch();
  BlockLeftMargin               = 100;
  BlockRightMargin              = 100;
  EndOfSentencePadding          = 3;
  EndOfPhrasePadding            = 2;
  BlockLinesAreJustified        = false;
  
  if ( DotsPerInchX ) {
    BlockLeftMargin             = DotsPerInchX;
    BlockRightMargin            = DotsPerInchX;
  }
  
  mode                          = ReferenceMode;
  displayFont                   = QFont("Times New Roman ", 16, QFont::Normal);
  
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
  emit SignalVerseCountChanged(verseCount);
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
  switch (mode) {
    case NoneMode : {
      break;
    }
    case ReferenceMode : {
      height = ArrangeItemsReference(x, y, windowWidth);
      emit SignalVerseCountChanged(GetVerseCount());
      break;
    }
    case BlockMode : {
      windowWidth = tableWidth - (BlockLeftMargin + BlockRightMargin);
      height = ArrangeItemsBlock(BlockLeftMargin, y, windowWidth);
      break;
    }
    case EditMode : {
      height = ArrangeItemsEdit(x, y, windowWidth);
      break;
    }
    case SentenceMode : {
      height = ArrangeItemsSentence(x, y, windowWidth);
      emit SignalSentenceCountChanged(tmpSentenceCount);
      break;
    }
  }
  windowSize = QSize(tableWidth, height);
  resize(windowSize);
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
  int                                   i;
  int                                   n;
  TextDisplayItem*                      item;
  
  x             = InX;
  y             = InY;
  windowHeight  = 0;

  n = textItems.size();
  for ( i = 0 ; i < n ; i++ ) {
    item = textItems[i];
    s = item->GetSize();
    itemWidth = s.width();
    itemHeight = s.height();
    itemText = item->GetText();
    ending = itemText.right(1);

    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }
    if ( itemWidth + x >= InWindowWidth ) {
      x = InX + sentenceIndent;
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
      x = InX;
      windowHeight = y + itemHeight;
    }
  }
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
  int                                   formatting;
  int                                   i;
  int                                   n;
  QStringList                           words;
  TextDisplayItem*                      item;
  TextDisplayReferenceItem*             refItem;
  TextDisplayFormattingItem*            formattingItem;
  QString                               referenceText;

  refItem = new TextDisplayReferenceItem(bookInfo->index,
                                         bookInfo->GetCapitalizedBookName(),
                                         InChapter, InVerse);

  formatting = GetFormattingByReference(bookInfo->index, InChapter, InVerse);
  if ( formatting ) {
    formattingItem = new TextDisplayFormattingItem(bookInfo->index,
                                                   bookInfo->GetCapitalizedBookName(),
                                                   InChapter,
                                                   InVerse,
                                                   (TextDisplayFormattingItem::FormatType)formatting);
    formattingItems.push_back(formattingItem);
  }
  refItem->SetFont(displayFont);
  refItem->SetSize(QSize(referenceWidth, refItem->GetSize().height()));
  textItems.push_back(refItem);
  words = InVerseText.split(" ");
  n = words.size();

  for ( i = 0; i < n; i++ ) {
    item = new TextDisplayWordItem(bookInfo->index, InChapter, InVerse, words[i], i + 1);
    item->SetFont(displayFont);
    textItems.push_back(item);
    tmpVerseCount++;
    wordCount++;
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
  formattingItems.clear();
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
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetEditMode(void)
{
  mode = EditMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : GetFormattingByReference
 *****************************************************************************/
TextDisplayFormattingItem::FormatType
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
    return TextDisplayFormattingItem::FormatTypeNone;
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
  return (TextDisplayFormattingItem::FormatType)type;
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
  ArrangeItems();
  repaint();
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

  painter.setRenderHints(QPainter::Antialiasing);
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
    case EditMode : {
      PaintEditMode(&painter, rect);
      break;
    }
    case NoneMode : {
      break;
    }
  }
  painter.end();
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
 * Function : ArrangeItemsEdit
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsEdit
(int InX, int InY, int InWindowWidth)
{
  TextDisplayFormattingItem*            formattingItem;
  bool                                  isFirst;
  int                                   itemHeight;
  int                                   itemWidth;
  QSize                                 s;
  int                                   windowHeight;
  int                                   wordSkip;
  int                                   x;
  int                                   y;
  
  x             = InX;
  y             = InY;
  windowHeight  = 0;

  isFirst = false;
  do {
    for ( auto item : textItems ) {
      wordSkip = InterWordSkip;
      
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        x = leftMargin + EditViewReferenceIndent;
        if ( isFirst ) {
          y += InterLineSkip + itemHeight;
        }
        formattingItem = FindFormattingItem(item->GetBook(), item->GetChapter(), item->GetVerse());
        if ( formattingItem ) {
          formattingItem->SetLocation(QPoint(leftMargin, y + InterLineSkip));
          formattingItem->SetSize(QSize(EditViewReferenceIndent - leftMargin, itemHeight));
        }
        isFirst = true;
        windowHeight = y + itemHeight;
        item->SetLocation(QPoint(x, y));
        x += s.width() + wordSkip;
        continue;
      }

      if ( itemWidth + x >= InWindowWidth ) {
        x = leftMargin + referenceWidth + InterWordSkip + EditViewReferenceIndent;
        y += InterLineSkip + itemHeight;
        windowHeight = y + itemHeight;
      }

      item->SetLocation(QPoint(x, y));
      x += s.width() + wordSkip;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : PaintEditMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintEditMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;

  
  for ( auto item : textItems ) {
    itemR = QRect(item->GetBoundingRect());
    if ( ! InRect.contains(itemR) ) {
      continue;
    }
    if ( lastSelectedItem == item ) {
      item->DrawSelected(InPainter);
    } else {
      item->Draw(InPainter);
    }
  }
  for ( auto item : formattingItems ) {
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      item->Draw(InPainter);
    }
  }
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
 * Function : ArrangeItemsBlock
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsBlock
(int InX, int InY, int InWindowWidth)
{
  int                                   k;
  TextDisplayItem*                      item2;
  int                                   book;
  bool                                  breakAfter;
  int                                   chapter;
  QString                               ending;
  TextDisplayFormattingItem::FormatType formatting;
  int                                   i;
  TextDisplayItem*                      item;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   n;
  TextDisplayReferenceItem*             referenceItem;
  QSize                                 s;
  int                                   verse;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  int                                   lineEnd;
  int                                   lineStartIndex;
  int                                   lineEndIndex;
  QPoint                                location;
  TextDisplayItem::ParagraphPosition    paragraphPosition;
  
  lineEnd       = InX;
  x             = InX;
  y             = InY;
  windowHeight  = 0;
  breakAfter = false;
  lineStartIndex = 1;
  lineEndIndex = 0;
  n = textItems.size();
  paragraphPosition = TextDisplayItem::MidParagraph;
  
  do {
    for (i = 0; i < n; i++) {
      item = textItems[i];
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      itemText = item->GetText();
      ending = itemText.right(1);
      
      //!
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        if ( breakAfter ) {
          x = InX;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          breakAfter = false;
          paragraphPosition = TextDisplayItem::StartOfParagraph;
          k = i - 1;
          while ( k > 1 ) {
            item2 = textItems[k];
            if ( item2->GetType() == TextDisplayItem::TextType ) {
              item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
              break;
            }
            k--;
          }
        }
        referenceItem = (TextDisplayReferenceItem*)item;
        verse = referenceItem->GetVerse();
        chapter = referenceItem->GetChapter();
        book = bookInfo->index;
        formatting = GetFormattingByReference(book, chapter, verse);
        if ( formatting == TextDisplayFormattingItem::FormatTypePostVerse ) {
          breakAfter = true;
          continue;
        }
        if ( formatting == TextDisplayFormattingItem::FormatTypePreVerse ) {
          k = i - 1;
          while ( k > 1 ) {
            item2 = textItems[k];
            if ( item2->GetType() == TextDisplayItem::TextType ) {
              item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
              break;
            }
            k--;
          }
          x = InX;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          paragraphPosition = TextDisplayItem::StartOfParagraph;
          continue;
        }
        continue;
      }
      //!
      if ( itemWidth + x >= InWindowWidth ) {
        if ( BlockLinesAreJustified ) {
          LineJustify(InWindowWidth, lineEnd, lineStartIndex, lineEndIndex);
        }
        x = InX;
        lineEnd = x;
        y += itemHeight;
        windowHeight = y + itemHeight;
        lineStartIndex = i;
        location = QPoint(x, y);
        item->SetLocation(QPoint(x, y));
        x += itemWidth + InterWordSkip;
        lineEnd = x - InterWordSkip;
        lineEndIndex = i;
        continue;
      }

      //!
      location = QPoint(x, y);
      item->SetLocation(location);
      item->SetParagraphPosition(paragraphPosition);
      x += itemWidth + InterWordSkip;
      lineEnd = x - InterWordSkip;
      lineEndIndex = i;
      paragraphPosition = TextDisplayItem::MidParagraph;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : PaintBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintBlockMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;

  QBrush                                brush = QBrush(MainSystemConfig->GetBlockWindowBackgroundColor());
  QSize                                 s = size();
  InPainter->setBrush(brush);
  InPainter->drawRect(QRect(QPoint(0, 0), s));
  
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
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayViewWindow::mousePressEvent
(QMouseEvent* InEvent)
{
  QPoint                                p = InEvent->position().toPoint();
  if ( mode == EditMode ) {
    EditModeMousePress(p);
    return;
  }
}

/*****************************************************************************!
 * Function : EditModeMousePress
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeMousePress
(QPoint InPoint)
{
  TextDisplayItem*                      item;
  TextDisplayItem::DisplayType          type;

  item = FindSelectedItem(InPoint);
  if ( NULL == item ) {
    return;
  }
  type = item->GetType();
  if ( type == TextDisplayItem::ReferenceType ) {
    EditModeReferenceMouseSelect((TextDisplayReferenceItem*)item);
    return;
  }
  if ( type == TextDisplayItem::WordType ) {
    EditModeWordMouseSelect((TextDisplayWordItem*)item);
    return;
  }
}

/*****************************************************************************!
 * Function : FindSelectedItem
 *****************************************************************************/
TextDisplayItem*
TextDisplayViewWindow::FindSelectedItem
(QPoint InLocation)
{
  for ( auto item : textItems ) {
    if ( item->Contains(InLocation) ) {
      return item;
    }
  }
  return NULL;
}
    
/*****************************************************************************!
 * Function : EditModeReferenceMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeReferenceMouseSelect
(TextDisplayReferenceItem* InItem)
{
  int                                   verse;
  int                                   chapter;
  int                                   book;
  QString                               itemText;

  itemText = InItem->GetText();
  book = InItem->GetBook();
  chapter = InItem->GetChapter();
  verse = InItem->GetVerse();

  AddFormatting(book, chapter, verse, 0, TextDisplayFormattingItem::FormatTypePreVerse);
}

/*****************************************************************************!
 * Function : AddFormatting
 *****************************************************************************/
void
TextDisplayViewWindow::AddFormatting
(int InBook, int InChapter, int InVerse, int InWord, int InFormatting)
{
  int                                   m;
  char                                  sqlstatement[1024];
  QString                               insertStatment;
  TextDisplayFormattingItem*            formattingItem;
  
  insertStatment = SQLStatement::GetFormattingInsert();
  sprintf(sqlstatement,
          insertStatment.toStdString().c_str(),
          InBook,
          InChapter,
          InVerse,
          InWord,
          QString(),
          InFormatting);
  m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, NULL);
  if ( m != SQLITE_OK ) {
    fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
    return;
  }
  bookInfo = FindBookInfoByIndex(InBook);
  if ( bookInfo == NULL ) {
    return;
  }
  formattingItem = new TextDisplayFormattingItem(InBook, bookInfo->name, InChapter, InVerse,
                                                 (TextDisplayFormattingItem::FormatType)InFormatting);
  formattingItems.push_back(formattingItem);
  ArrangeItems();
  repaint();
  return;
}


/*****************************************************************************!
 * Function : EditModeWordMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeWordMouseSelect
(TextDisplayWordItem* InItem)
{
  QString                               st;
  QString                               word;
  int                                   wordIndex;

  word = InItem->GetWord();
  wordIndex = InItem->GetWordIndex();
  st = QString("%1:%2").arg(word).arg(wordIndex);
  emit SignalSetMessage(st);
}
  
/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplayViewWindow::mouseMoveEvent
(QMouseEvent* InEvent)
{
  QString                               itemText;
  QPoint                                location;
  QString                               text;
  QPoint                                p = InEvent->position().toPoint();

  if ( mode == EditMode ) {
    EditModeMouseMove(p);
    return;
  }
  if ( lastSelectedItem && lastSelectedItem->Contains(p) ) {
    return;
  }

  lastSelectedItem = NULL;
  for ( auto item : textItems ) {
    if ( item->Contains(p) ) {
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        continue;
      }
      location = item->GetLocation();
      itemText = item->GetText();
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
 * Function : EditModeMouseMove
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeMouseMove
(QPoint InLocation)
{
  QPoint                                location;

  if ( lastSelectedItem && lastSelectedItem->Contains(InLocation) ) {
    return;
  }

  lastSelectedItem = NULL;
  for ( auto item : textItems ) {
    if ( item->Contains(InLocation) ) {
      location = item->GetLocation();
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

/*****************************************************************************!
 * Function : FindFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem*
TextDisplayViewWindow::FindFormattingItem
(int InBook, int InChapter, int InVerse)
{
  for ( auto item : formattingItems ) {
    if ( item->IsReference(InBook, InChapter, InVerse) ) {
      return item;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : LineJustify
 *****************************************************************************/
void
TextDisplayViewWindow::LineJustify
(int InWindowWidth, int InLineEnd, int InLineStartIndex, int InLineEndIndex)
{
  int                                   lineRemaining;

  lineRemaining = InWindowWidth - InLineEnd;
  lineRemaining = LineJustifyPunctuation(lineRemaining, InLineStartIndex, InLineEndIndex);
  LineJustifyWords(lineRemaining, InLineStartIndex, InLineEndIndex);
}

/*****************************************************************************!
 * Function : LineJustifyPunctuation
 *****************************************************************************/
int
TextDisplayViewWindow::LineJustifyPunctuation
(int InLineRemaining, int InLineStartIndex, int InLineEndIndex)
{
  QPoint                                Location;
  QString                               ending;
  TextDisplayItem*                      item;
  QString                               itemText;
  int                                   k;
  int                                   lineRemaining;

  //!
  lineRemaining = InLineRemaining;
  for ( int i = InLineStartIndex ; lineRemaining > 0 && i < InLineEndIndex ; i++ ) {
    item = textItems[i];
    itemText = item->GetText();
    if ( item->GetParagraphPosition() == TextDisplayItem::EndOfParagraph ) {
      continue;
    }
    ending = itemText.right(1);
    Location = item->GetLocation();
    if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
      k = itemText.length() - 2;
      ending = itemText.sliced(k, 1);

      //!
      if ( ending == "." || ending == "?" || ending == "!" ) {
        for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
          TextDisplayItem*              item1 = textItems[j];
          if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
            continue;
          }
          Location = item1->GetLocation();
          Location += QPoint(EndOfSentencePadding, 0);
          item1->SetLocation(Location);
        }
        lineRemaining -= EndOfSentencePadding;
        continue;
      }

      //!
      if ( ending == ":" || ending == ";" || ending == "," ) {
        for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
          TextDisplayItem*              item1 = textItems[j];
          if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
            continue;
          }
          Location = item1->GetLocation();
          Location += QPoint(EndOfPhrasePadding, 0);
          item1->SetLocation(Location);
        }
        lineRemaining -= EndOfPhrasePadding;
        continue;
      }
    }

    //!
    if ( ending == "." || ending == "?" || ending == "!" ) {
      for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location = item1->GetLocation();
        Location += QPoint(EndOfSentencePadding, 0);
        item1->SetLocation(Location);
      }
      lineRemaining -= EndOfSentencePadding;
      continue;
    }

    //!
    if ( ending == ":" || ending == ";" || ending == "," ) {
      for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        Location = item1->GetLocation();
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location += QPoint(EndOfPhrasePadding, 0);
        item1->SetLocation(Location);
      }
      lineRemaining -= EndOfPhrasePadding;
      continue;
    }
  }
  return lineRemaining;
}

/*****************************************************************************!
 * Function : LineJustifyWords
 *****************************************************************************/
void
TextDisplayViewWindow::LineJustifyWords
(int InLineRemaining, int InLineStartIndex, int InLineEndIndex)
{
  QSize                                 Size;
  QPoint                                Location;
  QString                               itemText;
  int                                   lineRemaining;
  TextDisplayItem*                      item;
  QString                               ending;

  lineRemaining = InLineRemaining;
  wordCount = InLineEndIndex - InLineStartIndex;
  while ( lineRemaining > 0 ) {
    for ( int i = InLineStartIndex ;  lineRemaining > 0 && i < InLineEndIndex ; i++ ) {
      item = textItems[i];
      itemText = item->GetText();
      ending = itemText.right(1);
      
      if ( WordEndsInPunctuation(itemText) ) {
        continue;
      }
      for ( int j = i + 1 ; lineRemaining > 0 && j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location = item1->GetLocation();
        itemText = item1->GetText();
        Location += QPoint(1, 0);
        Size = item1->GetSize();
        item1->SetLocation(Location);
      }
      lineRemaining--;
    }
  }
}

/*****************************************************************************!
 * Function : WordEndsInPunctuation
 *****************************************************************************/
bool
TextDisplayViewWindow::WordEndsInPunctuation
(QString InWord)
{
  QString ending =                      InWord.right(1);

  if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ||
       ending == ":" || ending == ";" || ending == "," ||
       ending == "." || ending == "?" || ending == "!" ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : FindBookInfoByIndex
 *****************************************************************************/
BookInfo*
TextDisplayViewWindow::FindBookInfoByIndex
(int InBookIndex)
{
  for ( auto bookInfo : MainBookInfo ) {
    if ( bookInfo->index == InBookIndex ) {
      return bookInfo;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : SlotSelectChapter
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSelectChapter
(int InChapter)
{
  QPoint                                loc;
  TextDisplayReferenceItem*             item;

  item = FindDisplayReferenceByChapterVerse(InChapter, 1);
  if ( NULL == item ) {
    return;
  }

  loc = item->GetLocation();
  emit SignalLocationSelected(loc);
}

/*****************************************************************************!
 * Function : FindDisplayReferenceByChapterVerse
 *****************************************************************************/
TextDisplayReferenceItem*
TextDisplayViewWindow::FindDisplayReferenceByChapterVerse
(int InChapter, int InVerse)
{
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      if ( item->GetChapter() == InChapter && item->GetVerse() == InVerse ) {
        return (TextDisplayReferenceItem*)item;
      }
    }
  }
  return NULL;
}
