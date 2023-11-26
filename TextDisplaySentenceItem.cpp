/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceItem.cpp
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
#include "TextDisplaySentenceItem.h"
#include "common.h"

/*****************************************************************************!
 * Function : TextDisplaySentenceItem
 *****************************************************************************/
TextDisplaySentenceItem::TextDisplaySentenceItem
(int InBook, int InChapter, int InVerse, QString InWord, int InWordIndex) : QLabel()
{
  QPalette                              pal;
  QRect                                 rect;
  int                                   height;
  QSize                                 s;
  
  StripQuotes = true;

  // setFrameShape(QFrame::Box);
  
  Book = InBook;
  Chapter = InChapter;
  Verse = InVerse;
  WordIndex = InWordIndex;
  Word = InWord;
  CreateStrippedWord();

  setText(GetWord());
  Foreground = QColor(80, 64, 42);
  Background = QColor(255, 255, 255);
  Font = QFont(MainSystemConfig->GetWordItemFont());
  setFont(Font);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  setIndent(0);
  QFontMetrics				fm(Font);

  rect = fm.boundingRect(StrippedWord);
  height = rect.height();
  s = QSize(rect.width()+4, height);
  resize(s);
  
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(Background));
  pal.setBrush(QPalette::WindowText, QBrush(Foreground));
  setPalette(pal);
}

/*****************************************************************************!
 * Function : ~TextDisplaySentenceItem
 *****************************************************************************/
TextDisplaySentenceItem::~TextDisplaySentenceItem
()
{
}

/*****************************************************************************!
 * Function : GetWordIndex
 *****************************************************************************/
int
TextDisplaySentenceItem::GetWordIndex(void)
{
  return WordIndex;  
}

/*****************************************************************************!
 * Function : SetWordIndex
 *****************************************************************************/
void
TextDisplaySentenceItem::SetWordIndex
(int InWordIndex)
{
  WordIndex = InWordIndex;  
}

/*****************************************************************************!
 * Function : GetWord
 *****************************************************************************/
QString
TextDisplaySentenceItem::GetWord(void)
{
  if ( ! StripQuotes ) {
    return Word;
  }
  return StrippedWord;
}

/*****************************************************************************!
 * Function : CreateStrippedWord
 *****************************************************************************/
void
TextDisplaySentenceItem::CreateStrippedWord
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
TextDisplaySentenceItem::GetText(void)
{
  return GetWord();  
}

/*****************************************************************************!
 * Function : SetWord
 *****************************************************************************/
void
TextDisplaySentenceItem::SetWord
(QString InWord)
{
  Word = InWord;
  CreateStrippedWord();
}

/*****************************************************************************!
 * Function : SetFont
 *****************************************************************************/
void
TextDisplaySentenceItem::SetFont
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
TextDisplaySentenceItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : IsReference
 *****************************************************************************/
bool
TextDisplaySentenceItem::IsReference
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
TextDisplaySentenceItem::GetSize()
{
  return size();
}
