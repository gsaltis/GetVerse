/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearItem.cpp
 * DATE         : September 16 2023
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
#include "TextDisplayInterlinearItem.h"
#include "common.h"
#include "StrongsReferenceDisplayDialog.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
bool
TextDisplayInterlinearItem::DisplayEnglish = true;

bool
TextDisplayInterlinearItem::DisplayContextual = true;

bool
TextDisplayInterlinearItem::DisplayStrongs = true;

bool
TextDisplayInterlinearItem::DisplayMorphology = true;

bool
TextDisplayInterlinearItem::DisplayTransliterate = true;

/*****************************************************************************!
 * Function : TextDisplayInterlinearItem
 *****************************************************************************/
TextDisplayInterlinearItem::TextDisplayInterlinearItem
(InterlinearWord* InWord, int InWordIndex, QWidget* InParent, int InRightToLeft) : QFrame(InParent)
{
  WordIndex     = InWordIndex;
  Word          = InWord;

  setFrameShape(QFrame::Panel);
  setFrameStyle(QFrame::Plain);
  setLineWidth(1);
  
  RightToLeft = InRightToLeft;
  
  Background = QColor(255, 255, 255);
  OverBackground = QColor(208, 208, 208); 

  CreateStrongsLabel();
  CreateContextualLabel();
  CreateEnglishLabel();
  CreateTransliterateLabel();
  CreateMorphologyLabel();
  ComputeSize();
  
  resize(Size);
  
  setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearItem
 *****************************************************************************/
TextDisplayInterlinearItem::~TextDisplayInterlinearItem
()
{
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayInterlinearItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
TextDisplayInterlinearItem::GetSize()
{
  return Size;
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayInterlinearItem::enterEvent
(QEnterEvent* )
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(OverBackground));
  setPalette(pal);
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
TextDisplayInterlinearItem::leaveEvent
(QEvent* )
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(Background));
  setPalette(pal);
}

/*****************************************************************************!
 * Function : CreateEnglishLabel
 *****************************************************************************/
void
TextDisplayInterlinearItem::CreateEnglishLabel(void)
{
  int                                   height;
  int                                   width;
  QRect                                 rect;
  QPalette                              pal;
  QString                               text;
  QFontMetrics                          metric(Word->englishFont);

  setLineWidth(1);
  EnglishLabel = new QLabel(this);

  EnglishLabel->setFont(Word->englishFont);
  text = Word->GetEnglish();
  text = text.trimmed();
  EnglishLabel->setText(text);

  pal = EnglishLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(Word->englishColor));
  EnglishLabel->setPalette(pal);
  EnglishLabel->setAutoFillBackground(true);
  
  rect = metric.boundingRect(text);
  width = rect.width();

  height = rect.height();
  EnglishSize = QSize(width, height);
  EnglishLabel->resize(EnglishSize);
}

/*****************************************************************************!
 * Function : CreateStrongsLabel
 *****************************************************************************/
void
TextDisplayInterlinearItem::CreateStrongsLabel(void)
{
  int                                   height;
  int                                   width;
  QRect                                 rect;
  QPalette                              pal;
  QString                               text;
  QFontMetrics                          metric(Word->strongsFont);

  setLineWidth(1);
  StrongsLabel = new QLabel(this);

  StrongsLabel->setFont(Word->strongsFont);
  text = Word->GetStrongsWordID();
  text = text.trimmed();
  StrongsLabel->setText(text);

  pal = StrongsLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(Word->strongsColor));
  StrongsLabel->setPalette(pal);
  StrongsLabel->setAutoFillBackground(true);
  
  rect = metric.boundingRect(text);
  width = rect.width() + 2;

  height = rect.height();
  StrongsSize = QSize(width, height);
  StrongsLabel->resize(StrongsSize);
}

/*****************************************************************************!
 * Function : CreateMorphologyLabel
 *****************************************************************************/
void
TextDisplayInterlinearItem::CreateMorphologyLabel(void)
{
  int                                   height;
  int                                   width;
  QRect                                 rect;
  QPalette                              pal;
  QString                               text;
  QFontMetrics                          metric(Word->morphologyFont);

  setLineWidth(1);
  MorphologyLabel = new QLabel(this);

  MorphologyLabel->setFont(Word->morphologyFont);
  text = Word->GetMorphologyID();
  text = text.trimmed();
  MorphologyLabel->setText(text);

  pal = MorphologyLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(Word->morphologyColor));
  MorphologyLabel->setPalette(pal);
  MorphologyLabel->setAutoFillBackground(true);
  
  rect = metric.boundingRect(text);
  width = rect.width() + 2;

  height = rect.height();
  MorphologySize = QSize(width, height);
  MorphologyLabel->resize(MorphologySize);
  MorphologyLabel->setAlignment(Qt::AlignRight);
}

/*****************************************************************************!
 * Function : CreateTransliterateLabel
 *****************************************************************************/
void
TextDisplayInterlinearItem::CreateTransliterateLabel(void)
{
  int                                   height;
  int                                   width;
  QRect                                 rect;
  QPalette                              pal;
  QString                               text;
  QFontMetrics                          metric(Word->transliterateFont);

  setLineWidth(1);
  TransliterateLabel = new QLabel(this);

  TransliterateLabel->setFont(Word->transliterateFont);
  text = Word->GetTransliteratedContextualForm();
  text = text.trimmed();
  TransliterateLabel->setText(text);

  pal = TransliterateLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(Word->transliterateColor));
  TransliterateLabel->setPalette(pal);
  TransliterateLabel->setAutoFillBackground(true);
  
  rect = metric.boundingRect(text);
  width = rect.width() + 2;

  height = rect.height();
  TransliterateSize = QSize(width, height);
  TransliterateLabel->resize(TransliterateSize);
}

/*****************************************************************************!
 * Function : CreateContextualLabel
 *****************************************************************************/
void
TextDisplayInterlinearItem::CreateContextualLabel(void)
{
  int                                   height;
  int                                   width;
  QRect                                 rect;
  QPalette                              pal;
  QString                               text;
  QFontMetrics                          metric(Word->contextualFormFont);

  setLineWidth(1);
  ContextualLabel = new QLabel(this);

  ContextualLabel->setFont(Word->contextualFormFont);
  text = Word->GetContextualForm();
  text = text.trimmed();
  ContextualLabel->setText(text);

  pal = ContextualLabel->palette();
  pal.setBrush(QPalette::WindowText, QBrush(Word->contextualFormColor));
  ContextualLabel->setPalette(pal);
  ContextualLabel->setAutoFillBackground(true);
  
  rect = metric.boundingRect(text);
  width = rect.width();
  ContextualLabel->setAlignment(Qt::AlignLeft);
  

  height = rect.height();
  ContextualSize = QSize(width, height);
  ContextualLabel->resize(ContextualSize);
}

/*****************************************************************************!
 * Function : ComputeSize
 *****************************************************************************/
void
TextDisplayInterlinearItem::ComputeSize(void)
{
  int                                   morphologyX;
  int                                   strongsX;
  int                                   w2;
  Qt::Alignment                         alignment;
  int                                   y;
  int                                   height;
  int                                   width;
  
  int                                   contextualHeight;
  int                                   contextualWidth;

  int                                   morphologyHeight;
  int                                   morphologyWidth;

  int                                   englishHeight;
  int                                   englishWidth;
  int                                   strongsHeight;
  int                                   strongsWidth;
  int                                   transliterateHeight;
  int                                   transliterateWidth;

  width = 0;
  englishWidth = EnglishSize.width();
  englishHeight = EnglishSize.height();

  contextualWidth = ContextualSize.width();
  contextualHeight = ContextualSize.height();

  strongsWidth = StrongsSize.width();
  strongsHeight = StrongsSize.height();

  morphologyWidth = MorphologySize.width();
  morphologyHeight = MorphologySize.height();

  transliterateWidth = TransliterateSize.width();
  transliterateHeight = TransliterateSize.height();


  width = contextualWidth;
  //!
  if ( DisplayEnglish ) {
    if ( width < englishWidth ) {
      width = englishWidth;
    }
  }

  //!
  if ( DisplayTransliterate ) {
    if ( width < transliterateWidth ) {
      width = transliterateWidth;
    }
  }
  
  //!
  w2 = 0;
  do {
    if ( ! DisplayStrongs && ! DisplayMorphology ) {
      w2 = 0;
      break;
    }
    if ( DisplayStrongs && DisplayMorphology ) {
      w2 = strongsWidth + morphologyWidth + 5;
      break;
    }
    if ( DisplayStrongs ) {
      w2 = strongsWidth + 5;
      break;
    }

    w2 = morphologyWidth + 5;
  } while ( false ) ;
  
  if ( width < w2 ) {
    width = w2;
  }

  y = 0;

  //!
  do {
    if ( ! DisplayStrongs && ! DisplayMorphology ) {
      break;
    }
    if ( DisplayStrongs && DisplayMorphology )
    {
      StrongsLabel->move(0, y);
      morphologyWidth = width - (strongsWidth + 5);
      MorphologyLabel->move(strongsWidth + 5 , y);
      MorphologyLabel->resize(morphologyWidth, morphologyHeight);
      y += strongsHeight;
      break;
    }
    if ( DisplayStrongs ) {
      strongsX = width - (strongsWidth + 5);
      StrongsLabel->move(strongsX, y);
      y += strongsHeight;
      break;
    }
    // Display Morphology only
    morphologyX = width - (morphologyWidth + 5);
    MorphologyLabel->move(morphologyX, y);
    y += morphologyHeight;
  } while ( false ) ;
  //!
  ContextualLabel->move(0, y);
  y += contextualHeight;

  if ( DisplayEnglish ) {
    EnglishLabel->move(0, y);
    y += englishHeight;
  }

  if ( DisplayTransliterate ) {
    TransliterateLabel->move(0, y);
    y += transliterateHeight;
  }
  
  height = y;
  
  Size = QSize(width, height);

  EnglishLabel->resize(width, englishHeight);
  ContextualLabel->resize(width, contextualHeight);
  TransliterateLabel->resize(width, transliterateHeight);
  
  alignment = RightToLeft ? Qt::AlignRight  : Qt::AlignLeft;

  EnglishLabel->setAlignment(alignment);
  StrongsLabel->setAlignment(alignment);
  TransliterateLabel->setAlignment(alignment);
  
  resize(Size);
}

/*****************************************************************************!
 * Function : GetVerseNumber
 *****************************************************************************/
int
TextDisplayInterlinearItem::GetVerseNumber
()
{
  return Word->GetVerseNumber();
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayInterlinearItem::mousePressEvent
(QMouseEvent* InEvent)
{
  Qt::KeyboardModifiers                 modifiers;
  Qt::MouseButton                       button;

  button = InEvent->button();  
  modifiers = InEvent->modifiers();

  if ( ( modifiers == Qt::NoModifier ) && (button == Qt::LeftButton) ) {
    DisplayStrongsReference();
    return;
  }

  if ( ( modifiers == Qt::ControlModifier ) && ( button == Qt::LeftButton ) ) {
    DisplayStrongCrossReference();
    return;
  }
}

/*****************************************************************************!
 * Function : DisplayStrongsReference
 *****************************************************************************/
void
TextDisplayInterlinearItem::DisplayStrongsReference(void)
{
  QString                               strongsWord;
  StrongsReferenceDisplayDialog*        dialog;

  strongsWord = Word->GetStrongsWordID();
  if ( strongsWord == "-" ) {
    return;
  }
  dialog = new StrongsReferenceDisplayDialog(Word);
  dialog->exec();
  delete dialog;
  
}

/*****************************************************************************!
 * Function : DisplayStrongCrossReference
 *****************************************************************************/
void
TextDisplayInterlinearItem::DisplayStrongCrossReference(void)
{
  QString                               strongsWord;

  strongsWord = Word->GetStrongsWordID();
  if ( strongsWord == "-" ) {
    return;
  }

  emit SignalSelectStrongsWord(strongsWord);
}

/*****************************************************************************!
 * Function : Reset
 *****************************************************************************/
void
TextDisplayInterlinearItem::Reset(void)
{
  if ( DisplayEnglish ) {
    EnglishLabel->show();
  } else {
    EnglishLabel->hide();
  }
  if ( DisplayTransliterate ) {
    TransliterateLabel->show();
  } else {
    TransliterateLabel->hide();
  }
  if ( DisplayStrongs ) {
    StrongsLabel->show();
  } else {
    StrongsLabel->hide();
  }
  if ( DisplayMorphology ) {
    MorphologyLabel->show();
  } else {
    MorphologyLabel->hide();
  }
}

/*****************************************************************************!
 * Function : ReComputeSize
 *****************************************************************************/
void
TextDisplayInterlinearItem::ReComputeSize(void)
{
  ComputeSize();
  resize(Size);
}
