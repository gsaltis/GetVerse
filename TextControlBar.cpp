/*****************************************************************************
 * FILE NAME    : TextControlBar.cpp
 * DATE         : September 14 2023
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
#include "TextControlBar.h"

/*****************************************************************************!
 * Function : TextControlBar
 *****************************************************************************/
TextControlBar::TextControlBar
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextControlBar
 *****************************************************************************/
TextControlBar::~TextControlBar
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextControlBar::initialize()
{
  ButtonWidth = 25;
  ButtonHeight = 25;
  InterWordSkip = 5;
  RightMargin = 10;
  InitializeSubWindows();  
  CreateSubWindows();
  ActionReferenceButtonPushed = new QAction("ReferenceButtonPushed", this);
  connect(ActionReferenceButtonPushed, SIGNAL(triggered()), this, SLOT(SlotReferenceButtonPushed()));
  ActionEditButtonPushed = new QAction("EditButtonPushed", this);
  connect(ActionEditButtonPushed, SIGNAL(triggered()), this, SLOT(SlotEditButtonPushed()));
  ActionAnalyzeButtonPushed = new QAction("AnalyzeButtonPushed", this);
  connect(ActionAnalyzeButtonPushed, SIGNAL(triggered()), this, SLOT(SlotAnalyzeButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextControlBar::CreateSubWindows()
{
  int                                   x = 5;
  
  //! Create the ReferenceButton button
  ReferenceButton = new QPushButton();
  ReferenceButton->setParent(this);
  ReferenceButton->setText("R");
  ReferenceButton->move(x, 0);
  ReferenceButton->resize(ButtonWidth, ButtonHeight);
  ReferenceButton->setCheckable(true);
  connect(ReferenceButton, SIGNAL(pressed()), this, SLOT(SlotReferenceButtonPushed()));
  x += ButtonWidth + 1;
  ReferenceButton->setChecked(true);
  
  //! Create the SentenceView button
  SentenceViewButton = new QPushButton();
  SentenceViewButton->setParent(this);
  SentenceViewButton->setText("S");
  SentenceViewButton->move(x, 0);
  SentenceViewButton->resize(ButtonWidth, ButtonHeight);
  SentenceViewButton->setCheckable(true);
  connect(SentenceViewButton, SIGNAL(pressed()), this, SLOT(SlotSentenceViewButtonPushed()));
  x += ButtonWidth + 1;

  //! Create the BlockView button
  BlockViewButton = new QPushButton();
  BlockViewButton->setParent(this);
  BlockViewButton->setText("B");
  BlockViewButton->move(x, 0);
  BlockViewButton->resize(ButtonWidth, ButtonHeight);
  BlockViewButton->setCheckable(true);
  connect(BlockViewButton, SIGNAL(pressed()), this, SLOT(SlotBlockViewButtonPushed()));
  x += ButtonWidth + 1;

  //! Create the EditButton button
  EditButton = new QPushButton();
  EditButton->setParent(this);
  EditButton->setText("E");
  EditButton->move(x, 0);
  EditButton->resize(ButtonWidth, ButtonHeight);
  EditButton->setCheckable(true);
  connect(EditButton, SIGNAL(pressed()), this, SLOT(SlotEditButtonPushed()));
  x += ButtonWidth + 6;

  //! Create the AnalyzeButton button
  AnalyzeButton = new QPushButton();
  AnalyzeButton->setParent(this);
  AnalyzeButton->setText("A");
  AnalyzeButton->move(x, 0);
  AnalyzeButton->resize(ButtonWidth, ButtonHeight);
  AnalyzeButton->setCheckable(true);
  connect(AnalyzeButton, SIGNAL(pressed()), this, SLOT(SlotAnalyzeButtonPushed()));

  //! Create label
  WordLabel = new QLabel();
  WordLabel->setParent(this);
  WordLabel->move(10, 10);
  WordLabel->resize(100, 20);
  WordLabel->setText("Words :");
  WordLabel->setAlignment(Qt::AlignRight);
  WordLabel->setFont(QFont("Arial", 10, QFont::Normal));

  //! Create label
  WordCountLabel = new QLabel();
  WordCountLabel->setParent(this);
  WordCountLabel->move(10, 10);
  WordCountLabel->resize(100, 20);
  WordCountLabel->setText("00000000");
  WordCountLabel->setAlignment(Qt::AlignLeft);
  WordCountLabel->setFont(QFont("Arial", 10, QFont::Normal));

  //! Create label
  GroupingLabel = new QLabel();
  GroupingLabel->setParent(this);
  GroupingLabel->move(10, 10);
  GroupingLabel->resize(100, 20);
  GroupingLabel->setText("Verses :");
  GroupingLabel->setAlignment(Qt::AlignRight);
  GroupingLabel->setFont(QFont("Arial", 10, QFont::Normal));

  //! Create label
  GroupingCountLabel = new QLabel();
  GroupingCountLabel->setParent(this);
  GroupingCountLabel->move(10, 10);
  GroupingCountLabel->resize(100, 20);
  GroupingCountLabel->setText("00000000");
  GroupingCountLabel->setAlignment(Qt::AlignLeft);
  GroupingCountLabel->setFont(QFont("Arial", 10, QFont::Normal));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextControlBar::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextControlBar::resizeEvent
(QResizeEvent* InEvent)
{
  QPalette                              pal;
  QSize					size;  
  int					height;
  int					width;
  int                                   WordLabelX;
  int                                   WordLabelY;
  int                                   WordLabelW;
  int                                   WordLabelH;
  int                                   WordCountLabelX;
  int                                   WordCountLabelY;
  int                                   WordCountLabelW;
  int                                   WordCountLabelH;

  int                                   GroupingLabelX;
  int                                   GroupingLabelY;
  int                                   GroupingLabelW;
  int                                   GroupingLabelH;
  int                                   GroupingCountLabelX;
  int                                   GroupingCountLabelY;
  int                                   GroupingCountLabelW;
  int                                   GroupingCountLabelH;
  
  size = InEvent->size();
  height = size.height();
  width  = size.width();

  //!
  QLinearGradient                       grad(0, 0, 0, height);
  {
    QFontMetrics                        fm(WordLabel->font());
    QSize                               s = fm.size(0, WordLabel->text());
    WordLabelW = s.width();
    WordLabelH = s.height();
  }

  //!
  {
    QFontMetrics                        fm(WordCountLabel->font());
    QSize                               s = fm.size(0, "000000");
    WordCountLabelW = s.width();
    WordCountLabelH = s.height();
  }

  {
    QFontMetrics                        fm(GroupingLabel->font());
    QSize                               s = fm.size(0, "MMMMMMMMMMMM");
    GroupingLabelW = s.width();
    GroupingLabelH = s.height();
  }

  //!
  {
    QFontMetrics                        fm(GroupingCountLabel->font());
    QSize                               s = fm.size(0, "000000");
    GroupingCountLabelW = s.width();
    GroupingCountLabelH = s.height();
  }
  
  //!
  WordCountLabelX = width - (WordCountLabelW + RightMargin);
  WordCountLabelY = (height - WordCountLabelH) / 2;

  WordLabelX = width - (WordCountLabelW + WordLabelW + RightMargin + InterWordSkip);
  WordLabelY = (height - WordLabelH) / 2;
  
  GroupingCountLabelX = width - (GroupingCountLabelW + WordLabelW + WordCountLabelW + 20 + RightMargin);
  GroupingCountLabelY = (height - GroupingCountLabelH) / 2;

  GroupingLabelX = width - (GroupingLabelW + GroupingCountLabelW + WordLabelW + WordCountLabelW + 25 + RightMargin);
  GroupingLabelY = (height - GroupingLabelH) / 2;
  
  WordLabel->move(WordLabelX, WordLabelY);
  WordLabel->resize(WordLabelW, WordLabelH);
  
  WordCountLabel->move(WordCountLabelX, WordCountLabelY);
  WordCountLabel->resize(WordCountLabelW, WordCountLabelH);

  GroupingLabel->move(GroupingLabelX, GroupingLabelY);
  GroupingLabel->resize(GroupingLabelW, GroupingLabelH);
  
  GroupingCountLabel->move(GroupingCountLabelX, GroupingCountLabelY);
  GroupingCountLabel->resize(GroupingCountLabelW, GroupingCountLabelH);

  grad.setColorAt(0, QColor(137, 137, 145));
  grad.setColorAt(1, QColor(241, 244, 255));
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(grad));
  setPalette(pal);
}

/*****************************************************************************!
 * Function : SlotReferenceButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotReferenceButtonPushed(void)
{
  GroupingLabel->setText("Verses :");
  GroupingCountLabel->setText("0");
  EditButton->setChecked(false);  
  BlockViewButton->setChecked(false);
  SentenceViewButton->setChecked(false);  
  GroupingLabel->show();
  GroupingCountLabel->show();
  emit SignalSetReferenceMode();
}

/*****************************************************************************!
 * Function : SlotBlockViewButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotBlockViewButtonPushed(void)
{
  ReferenceButton->setChecked(false);
  SentenceViewButton->setChecked(false);  
  EditButton->setChecked(false);  
  GroupingLabel->hide();
  GroupingCountLabel->hide();
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSentenceViewButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotSentenceViewButtonPushed(void)
{
  GroupingLabel->setText("Sentences :");
  GroupingCountLabel->setText("0");
  EditButton->setChecked(false);  
  GroupingLabel->show();
  GroupingCountLabel->show();
  ReferenceButton->setChecked(false);
  BlockViewButton->setChecked(false);
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotEditButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotEditButtonPushed(void)
{
  GroupingLabel->setText("Verses :");
  GroupingCountLabel->setText("0");
  BlockViewButton->setChecked(false);
  SentenceViewButton->setChecked(false);  
  EditButton->setChecked(true);  
  GroupingLabel->show();
  GroupingCountLabel->show();
  emit SignalSetEditMode();
}

/*****************************************************************************!
 * Function : SlotAnalyzeButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotAnalyzeButtonPushed(void)
{
  
}

/*****************************************************************************!
 * Function : SlotWordCountChanged
 *****************************************************************************/
void
TextControlBar::SlotWordCountChanged
(int InWordCount)
{
  WordCountLabel->setText(QString("%1").arg(InWordCount));
}

/*****************************************************************************!
 * Function : SlotVerseCountChanged
 *****************************************************************************/
void
TextControlBar::SlotVerseCountChanged
(int InVerseCount)
{
  GroupingCountLabel->setText(QString("%1").arg(InVerseCount));
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextControlBar::SlotSentenceCountChanged
(int InSentenceCount)
{
  GroupingCountLabel->setText(QString("%1").arg(InSentenceCount));
}
