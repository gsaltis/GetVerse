/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewWindow.cpp
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QScrollBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayReaderViewWindow.h"
#include "VerseInfoSet.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayReaderViewWindow
 *****************************************************************************/
TextDisplayReaderViewWindow::TextDisplayReaderViewWindow
(QWidget* InParent) : QTextEdit(InParent)
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 0, 0)));
  setPalette(pal);
  Initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayReaderViewWindow
 *****************************************************************************/
TextDisplayReaderViewWindow::~TextDisplayReaderViewWindow
()
{
  
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
TextDisplayReaderViewWindow::Initialize()
{
  setReadOnly(false);
  setAlignment(Qt::AlignJustify);
  setLineWidth(0);
  setFrameShape(QFrame::NoFrame);
  setFont(QFont(MainSystemSettings->GetReaderViewFontName(),
                MainSystemSettings->GetReaderViewFontSize(),
                QFont::Normal));
  Book = NULL;
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotBookSelected
(BookInfo* InBook)
{
  int                                   lastChapter;
  int                                   chapter;
  QString                               t;
  int                                   k;
  QTextDocument*                        doc;
  VerseInfo*                            verseInfo;
  int                                   i;
  QString                               text;
  QString                               verseText;
  VerseInfoSet*                         verseSet;
  int                                   verseCount;
  QTextBlockFormat                      textBlockFormat;
  QTextCursor                           cursor;

  //!
  k = 0;
  Book = InBook;
  verseSet = Book->GetVerses();

  
  //! 
  doc = document();
  cursor = QTextCursor(doc);
  cursor.setPosition(0);
  setPlainText("");

  //! 
  verseCount = verseSet->GetVerseCount();
  lastChapter = 1;
  for (i = 0 ; i < verseCount; i++) {
    verseInfo = verseSet->GetVerseByIndex(i);
    chapter = verseInfo->GetChapter();
    if ( chapter != lastChapter ) {
      CreateChapterBlock(cursor, 0);
      cursor.insertText(text);
      text = "";
      lastChapter = chapter;
    }
    t = verseInfo->GetText();
    text +=  t + QString(" ");
    k += t.length() + 1;
  }

  //!
  cursor.insertText(text);
  delete verseSet;
  setFocus();
  verticalScrollBar()->setValue(0);
  CreateConnections();
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotChapterSelected
(int)
{

}

/*****************************************************************************!
 * Function : CreateParagraphBlock
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateParagraphBlock
(QTextCursor& InCursor, uint32_t InPosition,
 int InLeftIndent, int InRightIndent,
 int InTopIndent, int InBottomIndent)
{
  QTextBlockFormat                      textBlockFormat;

  InCursor.setPosition(InPosition);
  textBlockFormat.setAlignment(Qt::AlignJustify);
  textBlockFormat.setLeftMargin(InLeftIndent);
  textBlockFormat.setRightMargin(InRightIndent);
  textBlockFormat.setTopMargin(InTopIndent);
  textBlockFormat.setBottomMargin(InBottomIndent);
  InCursor.insertBlock(textBlockFormat);
}

/*****************************************************************************!
 * Function : CreateChapterBlock
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateChapterBlock
(QTextCursor& InCursor, uint32_t InIndent)
{
  QTextBlockFormat                      textBlockFormat;

  textBlockFormat.setAlignment(Qt::AlignJustify);
  textBlockFormat.setBottomMargin(InIndent);
  textBlockFormat.setRightMargin(InIndent);
  textBlockFormat.setLeftMargin(InIndent);
  InCursor.insertBlock(textBlockFormat);
}

/*****************************************************************************!
 * Function : CreateCharBlock
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateCharBlock
(QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QColor InColor)
{
  QTextCharFormat                       charFormat;
  
  InCursor.setPosition(InStart);
  InCursor.setPosition(InEnd, QTextCursor::KeepAnchor);
  charFormat.setForeground(InColor);
  InCursor.mergeCharFormat(charFormat);
}

/*****************************************************************************!
 * Function : CreateCharBackgroundBlock
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateCharBackgroundBlock
(QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QColor InColor)
{
  QTextCharFormat                       charFormat;
  
  InCursor.setPosition(InStart);
  InCursor.setPosition(InEnd, QTextCursor::KeepAnchor);
  charFormat.setBackground(InColor);
  InCursor.mergeCharFormat(charFormat);
}

/*****************************************************************************!
 * Function : CreateCharFontBlock
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateCharFontBlock
(QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QFont InFont)
{
  QTextCharFormat                       charFormat;
  
  InCursor.setPosition(InStart);
  InCursor.setPosition(InEnd, QTextCursor::KeepAnchor);
  charFormat.setFont(InFont);
  InCursor.mergeCharFormat(charFormat);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateConnections(void)
{
  connect(this,
          QTextEdit::cursorPositionChanged,
          this,
          TextDisplayReaderViewWindow::SlotCursorPositionChanged);
}

/*****************************************************************************!
 * Function : SlotCursorPositionChanged
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotCursorPositionChanged(void)
{
  int                                   start;
  int                                   end;
  int                                   p;
  QTextCursor                           cursor = textCursor();
  
  start = cursor.selectionStart();
  end = cursor.selectionEnd();
  p = cursor.position();
  selectionStart = 0;
  currentCursorIndex = p;
  selectionStart = 0;
  selectionEndWord = 0;
  selectionStartWord = 0;
  if ( cursor.hasSelection() ) {
    selectionStart = start;
    selectionEnd = end;
    selectionStartWord = FindWordIndexAtPosition(selectionStart);
    selectionEndWord = FindWordIndexAtPosition(selectionEnd);
  }
}

/*****************************************************************************!
 * Function : FindWordIndexAtPosition
 *****************************************************************************/
int
TextDisplayReaderViewWindow::FindWordIndexAtPosition
(int InCursorPosition)
{
  int                                   wordIndex;
  bool                                  inWord;
  QChar                                 ch;
  int                                   i;
  QTextDocument*                        doc;
  
  wordIndex = 0;
  inWord = false;
  doc = document();
  for (i = 0; i < InCursorPosition; i++) {
    ch = doc->characterAt(i);
    if ( ch.isSpace() ) {
      inWord = false;
      continue;
    }
    if ( ! inWord ) {
      inWord = true;
      wordIndex++;
    }
  }
  return wordIndex;
}

/*****************************************************************************!
 * Function : SlotTextColorSet
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotTextColorSet
(QColor InTextColor)
{
  QTextCursor                                   cursor(document());
  
  if ( selectionStart > 0 && selectionEnd > 0 ) {
    CreateCharBlock(cursor, selectionStart, selectionEnd, InTextColor);
  }
}

/*****************************************************************************!
 * Function : SlotTextBackgroundColorSet
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotTextBackgroundColorSet
(QColor InTextBackgroundColor)
{
  QTextCursor                                   cursor(document());
  
  if ( selectionStart > 0 && selectionEnd > 0 ) {
    CreateCharBackgroundBlock(cursor, selectionStart, selectionEnd, InTextBackgroundColor);
  }
}

/*****************************************************************************!
 * Function : SlotTextFontSet
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotTextFontSet
(QFont InTextFont)
{
  QTextCursor                                   cursor(document());
  if ( selectionStart > 0 && selectionEnd > 0 ) {
    CreateCharFontBlock(cursor, selectionStart, selectionEnd, InTextFont);
  }
}

/*****************************************************************************!
 * Function : SlotParagraphSet
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotParagraphSet
(int InLeftIndent, int InRightIndent, int InTopIndent, int InBottomIndent)
{
  QTextCursor                                   cursor(document());
  CreateParagraphBlock(cursor, currentCursorIndex, InLeftIndent, InRightIndent, InTopIndent, InBottomIndent);
}

/*****************************************************************************!
 * Function : SlotExtraPushed
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotExtraPushed
()
{
  int                                   i;
  int                                   type;
  int                                   n;
  QList<QTextFormat>                    formats;
  
  TRACE_FUNCTION_START();
  formats = document()->allFormats();
  n = formats.size();
  TRACE_FUNCTION_INT(n);
  for (i = 0; i < n; i++) {
    type = formats[i].type();
    TRACE_FUNCTION_INT(type);
  }

  TRACE_FUNCTION_END();
}
