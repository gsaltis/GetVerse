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
#include "Trace.h"

/*****************************************************************************!
 * Static Elements
 *****************************************************************************/
QFont 	InterlinearWord::contextualFormFont  = QFont("Times New Roman", 18);
QColor  InterlinearWord::contextualFormColor = QColor("#f00000");

QFont 	InterlinearWord::englishFont         = QFont("Times New Roman", 12);
QColor  InterlinearWord::englishColor        = QColor("#DDDDDD");

QFont   InterlinearWord::strongsFont         = QFont("Times New Roman", 10, QFont::Bold);
QColor  InterlinearWord::strongsColor        = QColor("#00C000");

QFont   InterlinearWord::morphologyFont      = QFont("Times New Roman", 10);
QColor  InterlinearWord::morphologyColor     = QColor("#E000E0");

QFont   InterlinearWord::transliterateFont   = QFont("Times New Roman", 11);
QColor  InterlinearWord::transliterateColor  = QColor("#E0E0E0");

int     InterlinearWord::Lineskip            = 0;

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
  QFontMetrics							fm(contextualFormFont);
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
  QFontMetrics							fm(transliterateFont);
  QRect                                 rect;

  rect = fm.boundingRect(InTransliteratedContextualForm);
  transliterateSize = QSize(rect.width(), rect.height());
  TransliteratedContextualForm->SetText(InTransliteratedContextualForm);
}

/*****************************************************************************!
 * Function : SetMorphologyID
 *****************************************************************************/
void
InterlinearWord::SetMorphologyID
(QString InMorphologyID)
{
  QFontMetrics							fm(morphologyFont);
  QRect                                 rect;

  rect = fm.boundingRect(InMorphologyID);
  morphologySize = QSize(rect.width(), rect.height());
  MorphologyID->SetText(InMorphologyID);
}

/*****************************************************************************!
 * Function : SetStrongsWordID
 *****************************************************************************/
void
InterlinearWord::SetStrongsWordID
(QString InStrongsWordID)
{
  QFontMetrics							fm(strongsFont);
  QRect                                 rect;

  StrongsWordID->SetText(InStrongsWordID);
  rect = fm.boundingRect(InStrongsWordID);
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

  English->SetText(InEnglish);
  rect = fm.boundingRect(InEnglish);
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

  y1 = y;
  ws = GetSize();

  y1 += englishSize.height();
  InPainter->setPen(QPen(englishColor));
  InPainter->setBrush(QBrush(englishColor));
  InPainter->setFont(englishFont);
  offset = ws.width() - englishSize.width();
  text = English->GetText();
  InPainter->drawText(x + offset, y1, text);

  y1 += contextualFormSize.height() + Lineskip;
  InPainter->setPen(QPen(contextualFormColor));
  InPainter->setBrush(QBrush(contextualFormColor));
  InPainter->setFont(contextualFormFont);
  offset = ws.width() - contextualFormSize.width();
  text = ContextualForm->GetText();
  InPainter->drawText(x + offset, y1, text);

  y1 += strongsSize.height() + Lineskip;
  InPainter->setPen(QPen(strongsColor));
  InPainter->setBrush(QBrush(strongsColor));
  InPainter->setFont(strongsFont);
  offset = ws.width() - strongsSize.width();
  text = StrongsWordID->GetText();
  InPainter->drawText(x + offset, y1, text);

  y1 += morphologySize.height() + Lineskip;
  InPainter->setPen(QPen(morphologyColor));
  InPainter->setBrush(QBrush(morphologyColor));
  InPainter->setFont(morphologyFont);
  offset = ws.width() - morphologySize.width();
  text = MorphologyID->GetText();
  InPainter->drawText(x + offset, y1, text);

  y1 += transliterateSize.height() + Lineskip;
  InPainter->setPen(QPen(transliterateColor));
  InPainter->setBrush(QBrush(transliterateColor));
  InPainter->setFont(transliterateFont);
  offset = ws.width() - transliterateSize.width();
  text = TransliteratedContextualForm->GetText();
  InPainter->drawText(x + offset, y1, text);
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
InterlinearWord::GetSize
()
{
  int									width;
  int									height;
  int                                   cWidth;
  int                                   sWidth;
  int                                   mWidth;
  int                                   tWidth;
  QFontMetrics							fm1(englishFont);
  QFontMetrics                          fm2(contextualFormFont);
  QFontMetrics							fm3(strongsFont);
  QFontMetrics							fm4(morphologyFont);
  QFontMetrics							fm5(transliterateFont);
  QRect                                 si1 = fm1.boundingRect("Mg");
  QRect                                 si2 = fm2.boundingRect("Mg");
  QRect                                 si3 = fm3.boundingRect("Mg");
  QRect                                 si4 = fm4.boundingRect("Mg");
  QRect                                 si5 = fm5.boundingRect("Mg");

  width = englishSize.width();

  cWidth  = contextualFormSize.width();
  sWidth  = strongsSize.width();
  mWidth  = morphologySize.width();
  tWidth  = transliterateSize.width();

  if ( cWidth > width ) {
	width = cWidth;
  }

  if ( sWidth > width ) {
	width = sWidth;
  }

  if ( mWidth > width ) {
	width = mWidth;
  }

  if ( tWidth > width ) {
	width = tWidth;
  }

  height = si1.height() + si2.height() + si3.height() + si4.height() + si5.height() + 4 * Lineskip; 
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

