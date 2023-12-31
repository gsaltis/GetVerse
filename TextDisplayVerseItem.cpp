/*****************************************************************************
 * FILE NAME    : TextDisplayVerseItem.cpp
 * DATE         : September 16 2023
 * PROJECT      : 
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
 * Local Headers
 *****************************************************************************/
#include "TextDisplayVerseItem.h"
#include "common.h"

/*****************************************************************************!
 * Function : TextDisplayVerseItem
 *****************************************************************************/
TextDisplayVerseItem::TextDisplayVerseItem
(int InBook, int InChapter, int InVerse, QString InWord, int InWordIndex, QFont InFont) : QLabel()
{
  int                                   width;
  QPalette                              pal;
  QRect                                 rect;
  int                                   height;
  QSize                                 s;
  
  StripQuotes = false;

  // setFrameShape(QFrame::Box);
  
  Book          = InBook;
  Chapter       = InChapter;
  Verse         = InVerse;
  WordIndex     = InWordIndex;
  Word          = InWord;
  Font          = InFont;

  CreateStrippedWord();

  setText(GetWord());
  Foreground = QColor(80, 64, 42);
  Background = QColor(255, 255, 255);
  OverBackground = QColor(208, 208, 208); 
  setFont(Font);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  setIndent(0);
  QFontMetrics				fm(Font);

  rect = fm.boundingRect(Word);
  height = rect.height() + 4;
  width = rect.width() + 4;
  s = QSize(width, height);
  resize(s);
  
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(Background));
  pal.setBrush(QPalette::WindowText, QBrush(Foreground));
  setPalette(pal);
  setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : ~TextDisplayVerseItem
 *****************************************************************************/
TextDisplayVerseItem::~TextDisplayVerseItem
()
{
}

/*****************************************************************************!
 * Function : GetWordIndex
 *****************************************************************************/
int
TextDisplayVerseItem::GetWordIndex(void)
{
  return WordIndex;  
}

/*****************************************************************************!
 * Function : SetWordIndex
 *****************************************************************************/
void
TextDisplayVerseItem::SetWordIndex
(int InWordIndex)
{
  WordIndex = InWordIndex;  
}

/*****************************************************************************!
 * Function : GetWord
 *****************************************************************************/
QString
TextDisplayVerseItem::GetWord(void)
{
  if ( ! StripQuotes ) {
    return Word.trimmed();
  }
  return StrippedWord;
}

/*****************************************************************************!
 * Function : CreateStrippedWord
 *****************************************************************************/
void
TextDisplayVerseItem::CreateStrippedWord
()
{
  QString                       s;
  int                           n = Word.length();
  QChar                         ch;
  int                           i;

  s = QString();
  for (i = 0; i < n; i++) {
    ch = Word[i];
    if ( ch == '\'' || ch == '`' ) {
      continue;
    }
    s += ch;
  }
  StrippedWord = s.trimmed();
}

/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
TextDisplayVerseItem::GetText(void)
{
  return GetWord();  
}

/*****************************************************************************!
 * Function : SetWord
 *****************************************************************************/
void
TextDisplayVerseItem::SetWord
(QString InWord)
{
  Word = InWord;
  CreateStrippedWord();
}

/*****************************************************************************!
 * Function : SetFont
 *****************************************************************************/
void
TextDisplayVerseItem::SetFont
(QFont InFont)
{
  QFontMetrics                          fm(InFont);
  Font = QFont(InFont);
  Size = fm.size(0, GetWord());
  setFont(Font);
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayVerseItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : IsReference
 *****************************************************************************/
bool
TextDisplayVerseItem::IsReference
(const int InBook, const int InChapter, const int InVerse, const int InWord)
{
  if ( InBook == Book && InChapter == Chapter && InVerse == Verse && InWord == WordIndex ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
TextDisplayVerseItem::GetSize()
{
  return size();
}

/*****************************************************************************!
 * Function : GetVerseNumber
 *****************************************************************************/
int
TextDisplayVerseItem::GetVerseNumber(void)
{
  return Verse;
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
TextDisplayVerseItem::enterEvent
(QEnterEvent* )
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(OverBackground));
  setPalette(pal);
}

/*****************************************************************************!
 * 
 *****************************************************************************/
void
TextDisplayVerseItem::leaveEvent
(QEvent* )
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(Background));
  setPalette(pal);
}

