/*****************************************************************************
 * FILE NAME    : InterlinearWord.cpp
 * DATE         : October 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWord.h"
#include "main.h"

/*****************************************************************************!
 * Static Elements
 *****************************************************************************/
QFont 	InterlinearWord::contextualFormFont      = QFont("Times New Roman", 20, QFont::Bold);
QColor  InterlinearWord::contextualFormColor     = QColor("#800000");
bool    InterlinearWord::contextualFormDisplay   = true;

QFont 	InterlinearWord::englishFont             = QFont("Arial", 13);
QColor  InterlinearWord::englishColor            = QColor("#4444444");
bool    InterlinearWord::englishDisplay          = true;

QFont   InterlinearWord::strongsFont             = QFont("Arial", 9, QFont::Bold);
QColor  InterlinearWord::strongsColor            = QColor("#008000");
bool    InterlinearWord::strongsDisplay          = false;

QFont   InterlinearWord::morphologyFont          = QFont("Arial", 8);
QColor  InterlinearWord::morphologyColor         = QColor("#880088");
bool    InterlinearWord::morphologyDisplay       = false;

QFont   InterlinearWord::transliterateFont       = QFont("Arial", 11);
QColor  InterlinearWord::transliterateColor      = QColor("#444444");
bool    InterlinearWord::transliterateDisplay    = false;

int     InterlinearWord::Lineskip                = 0;

/*****************************************************************************!
 * Function : InterlinearWord
 *****************************************************************************/
InterlinearWord::InterlinearWord
(int InBookIndex, int InChapterNumber, int InVerseNumber, int InVerseID)
{
  BookIndex     = InBookIndex;
  ChapterNumber = InChapterNumber;
  VerseNumber   = InVerseNumber;
  VerseID       = InVerseID;
  selected      = false;

  ContextualForm                = new InterlinearWordText();
  TransliteratedContextualForm  = new InterlinearWordText();
  MorphologyID                  = new InterlinearWordText();
  StrongsWordID                 = new InterlinearWordText();
  English                       = new InterlinearWordText();
}

/*****************************************************************************!
 * Function : ~InterlinearWord
 *****************************************************************************/
InterlinearWord::~InterlinearWord
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
InterlinearWord::GetID
()
{
  return ID;
}

/*****************************************************************************!
 * Function : GetVerseID
 *****************************************************************************/
int
InterlinearWord::GetVerseID
()
{
  return VerseID;
}

/*****************************************************************************!
 * Function : GetContextualForm
 *****************************************************************************/
QString
InterlinearWord::GetContextualForm
()
{
  return ContextualForm->GetText();
}

/*****************************************************************************!
 * Function : GetTransliteratedContextualForm
 *****************************************************************************/
QString
InterlinearWord::GetTransliteratedContextualForm
()
{
  return TransliteratedContextualForm->GetText();
}

/*****************************************************************************!
 * Function : GetMorphologyID
 *****************************************************************************/
QString
InterlinearWord::GetMorphologyID
()
{
  return MorphologyID->GetText();
}

/*****************************************************************************!
 * Function : GetStrongsWordID
 *****************************************************************************/
QString
InterlinearWord::GetStrongsWordID
()
{
  return StrongsWordID->GetText();
}

/*****************************************************************************!
 * Function : GetEnglish
 *****************************************************************************/
QString
InterlinearWord::GetEnglish
()
{
  return English->GetText();
}

/*****************************************************************************!
 * Function : SetID
 *****************************************************************************/
void
InterlinearWord::SetID
(int InID)
{
  ID = InID;
}

/*****************************************************************************!
 * Function : SetVerseID
 *****************************************************************************/
void
InterlinearWord::SetVerseID
(int InVerseID)
{
  VerseID = InVerseID;
}

/*****************************************************************************!
 * Function : SetContextualForm
 *****************************************************************************/
void
InterlinearWord::SetContextualForm
(QString InContextualForm)
{
  QFontMetrics				fm(contextualFormFont);
  QRect                                 rect;
  int                                   height;

  ContextualForm->SetText(InContextualForm);
  rect = fm.boundingRect(InContextualForm);
  height = rect.height() / 2 + 5;
  contextualFormSize = QSize(rect.width(), height); 
}

/*****************************************************************************!
 * Function : SetTransliteratedContextualForm
 *****************************************************************************/
void
InterlinearWord::SetTransliteratedContextualForm
(QString InTransliteratedContextualForm)
{
  QFontMetrics				fm(transliterateFont);
  QRect                                 rect;

  TransliteratedContextualForm->SetText(InTransliteratedContextualForm.trimmed());
  rect = fm.boundingRect(TransliteratedContextualForm->GetText());
  transliterateSize = QSize(rect.width(), rect.height());
}

/*****************************************************************************!
 * Function : SetMorphologyID
 *****************************************************************************/
void
InterlinearWord::SetMorphologyID
(QString InMorphologyID)
{
  QFontMetrics				fm(morphologyFont);
  QRect                                 rect;

  MorphologyID->SetText(InMorphologyID.trimmed());
  rect = fm.boundingRect(MorphologyID->GetText());
  morphologySize = QSize(rect.width(), rect.height());
}

/*****************************************************************************!
 * Function : SetStrongsWordID
 *****************************************************************************/
void
InterlinearWord::SetStrongsWordID
(QString InStrongsWordID)
{
  QFontMetrics				fm(strongsFont);
  QRect                                 rect;

  StrongsWordID->SetText(InStrongsWordID);
  rect = fm.boundingRect(StrongsWordID->GetText());
  strongsSize = QSize(rect.width(), rect.height());
}

/*****************************************************************************!
 * Function : SetEnglish
 *****************************************************************************/
void
InterlinearWord::SetEnglish
(QString InEnglish)
{
  QFontMetrics							fm(englishFont);
  QRect                                 rect;

  English->SetText(InEnglish.trimmed());
  rect = fm.boundingRect(English->GetText());
  englishSize = QSize(rect.width(), rect.height());
}

/*****************************************************************************!
 * Function : Paint
 *****************************************************************************/
void
InterlinearWord::Paint
(QPainter* InPainter)
{
  QString                               text;
  int                                   y1;
  QSize                                 ws;
  int                                   offset;

#if 0
  int                                   x1, y2, y3;
#endif
  y1 = y;
  ws = GetSize();
#if 0
  InPainter->setPen(QPen(QColor("white")));
  x1 = x + ws.width();
  y2 = y;
  y3 = y + ws.height();
  InPainter->drawLine(x1, y2, x1, y3);
#endif

  if ( englishDisplay ) {
    y1 += englishSize.height();
    InPainter->setPen(QPen(englishColor));
    InPainter->setBrush(QBrush(englishColor));
    InPainter->setFont(englishFont);
    offset = ws.width() - englishSize.width();
    text = English->GetText();
    InPainter->drawText(x + offset, y1, text);
  }
  
  if ( contextualFormDisplay ) {
    y1 += contextualFormSize.height() + Lineskip;
    InPainter->setPen(QPen(contextualFormColor));
    InPainter->setBrush(QBrush(contextualFormColor));
    InPainter->setFont(contextualFormFont);
    offset = ws.width() - contextualFormSize.width();
    text = ContextualForm->GetText();
    InPainter->drawText(x + offset, y1, text);
  }

  if ( strongsDisplay ) {
    y1 += strongsSize.height() + Lineskip;
    InPainter->setPen(QPen(strongsColor));
    InPainter->setBrush(QBrush(strongsColor));
    InPainter->setFont(strongsFont);
    offset = ws.width() - strongsSize.width();
    text = StrongsWordID->GetText();
    InPainter->drawText(x + offset, y1, text);
  }

  if ( morphologyDisplay ) {
    y1 += morphologySize.height() + Lineskip;
    InPainter->setPen(QPen(morphologyColor));
    InPainter->setBrush(QBrush(morphologyColor));
    InPainter->setFont(morphologyFont);
    offset = ws.width() - morphologySize.width();
    text = MorphologyID->GetText();
    InPainter->drawText(x + offset, y1, text);
  }

  if ( transliterateDisplay ) {
    y1 += transliterateSize.height() + Lineskip;
    InPainter->setPen(QPen(transliterateColor));
    InPainter->setBrush(QBrush(transliterateColor));
    InPainter->setFont(transliterateFont);
    offset = ws.width() - transliterateSize.width();
    text = TransliteratedContextualForm->GetText();
    InPainter->drawText(x + offset, y1, text);
  }
}

/*****************************************************************************!
 * Function : PaintSelected
 *****************************************************************************/
void
InterlinearWord::PaintSelected
(QPainter* InPainter)
{
  QSize							s;
  QRect							r;

  InPainter->setPen(QPen(QColor(255, 255, 255, 64)));
  InPainter->setBrush(QBrush(QColor(128, 128, 128, 64)));
    
  s = GetSize();
  r = QRect(QPoint(x, y), s);
  InPainter->drawRoundedRect(r, 8, 8);
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
InterlinearWord::GetSize
()
{
  int					width;
  int					height;
  int                                   cWidth;
  int                                   sWidth;
  int                                   mWidth;
  int                                   tWidth;
  QFontMetrics				fm1(englishFont);
  QFontMetrics                          fm2(contextualFormFont);
  QFontMetrics				fm3(strongsFont);
  QFontMetrics				fm4(morphologyFont);
  QFontMetrics				fm5(transliterateFont);
  QRect                                 si1 = fm1.boundingRect("Mg");
  QRect                                 si2 = fm2.boundingRect("Mg");
  QRect                                 si3 = fm3.boundingRect("Mg");
  QRect                                 si4 = fm4.boundingRect("Mg");
  QRect                                 si5 = fm5.boundingRect("Mg");

  width = 0;

  cWidth  = contextualFormSize.width();
  sWidth  = strongsSize.width();
  mWidth  = morphologySize.width();
  tWidth  = transliterateSize.width();

  height = 0;
  if ( englishDisplay ) {
    width = englishSize.width();
    height += si1.height()  + Lineskip;
  }
  
  if ( contextualFormDisplay ) {
    if ( cWidth > width ) {
      width = cWidth;
    }
    height += si2.height() + Lineskip;
  }

  if ( strongsDisplay )  {
    if ( sWidth > width ) {
      width = sWidth;
    }
    height += si3.height()  + Lineskip;
  }

  if ( morphologyDisplay ) {
    if ( mWidth > width ) {
      width = mWidth;
    }
    height += si4.height() + Lineskip;
  }

  if ( transliterateDisplay ) {
    if ( tWidth > width ) {
      width = tWidth;
    }
    height += si5.height() + Lineskip;
  }

  return QSize(width, height);
}

/*****************************************************************************!
 * Function : SetLineskip
 *****************************************************************************/
void
InterlinearWord::SetLineskip
(int InLineskip)
{
  Lineskip = InLineskip;
}

/*****************************************************************************!
 * Function : ContainsPoint
 *****************************************************************************/
bool
InterlinearWord::ContainsPoint
(QPoint InPoint)
{
  QRect                                 rect;
  bool                                  b;

  rect = QRect(QPoint(x, y), GetSize());
  b = rect.contains(InPoint);
  return b;
}

/*****************************************************************************!
 * Function : SetSelected
 *****************************************************************************/
void
InterlinearWord::SetSelected
(bool InSelected)
{
  selected = InSelected;
}

/*****************************************************************************!
 * Function : GetValues
 *****************************************************************************/
void
InterlinearWord::GetValues
()
{
}

/*****************************************************************************!
 * Function : SetValues
 *****************************************************************************/
void
InterlinearWord::SetValues
()
{
}

/*****************************************************************************!
 * Function : GetVerseNumber
 *****************************************************************************/
int
InterlinearWord::GetVerseNumber(void)
{
  return VerseNumber;
}

/*****************************************************************************!
 * Function : GetChapterNumber
 *****************************************************************************/
int
InterlinearWord::GetChapterNumber(void)
{
  return ChapterNumber;
}
