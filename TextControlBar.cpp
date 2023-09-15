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
  //! Create the ReferenceButton button
  ReferenceButton = new QPushButton();
  ReferenceButton->setParent(this);
  ReferenceButton->setText("R");
  ReferenceButton->move(5, 0);
  ReferenceButton->resize(25,25);
  connect(ReferenceButton, SIGNAL(pressed()), this, SLOT(SlotReferenceButtonPushed()));

  //! Create the EditButton button
  EditButton = new QPushButton();
  EditButton->setParent(this);
  EditButton->setText("E");
  EditButton->move(31, 0);
  EditButton->resize(25,25);
  connect(EditButton, SIGNAL(pressed()), this, SLOT(SlotEditButtonPushed()));

  //! Create the AnalyzeButton button
  AnalyzeButton = new QPushButton();
  AnalyzeButton->setParent(this);
  AnalyzeButton->setText("A");
  AnalyzeButton->move(57, 0);
  AnalyzeButton->resize(25,25);
  connect(AnalyzeButton, SIGNAL(pressed()), this, SLOT(SlotAnalyzeButtonPushed()));

  //! Create the AnalyzeButton button
  BlockViewButton = new QPushButton();
  BlockViewButton->setParent(this);
  BlockViewButton->setText("B");
  BlockViewButton->move(83, 0);
  BlockViewButton->resize(25,25);
  connect(BlockViewButton, SIGNAL(pressed()), this, SLOT(SlotBlockViewButtonPushed()));

  //! Create label
  WordLabel = new QLabel();
  WordLabel->setParent(this);
  WordLabel->move(10, 10);
  WordLabel->resize(100, 20);
  WordLabel->setText("Words :");
  WordLabel->setAlignment(Qt::AlignRight);
  WordLabel->setFont(QFont("Arial", 10, QFont::Bold));

  //! Create label
  WordCountLabel = new QLabel();
  WordCountLabel->setParent(this);
  WordCountLabel->move(10, 10);
  WordCountLabel->resize(100, 20);
  WordCountLabel->setText("00000000");
  WordCountLabel->setAlignment(Qt::AlignLeft);
  WordCountLabel->setFont(QFont("Arial", 10, QFont::Normal));
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
    QSize                               s = fm.size(0, WordCountLabel->text());
    WordCountLabelW = s.width();
    WordCountLabelH = s.height();
  }

  //!
  WordCountLabelX = width - (WordCountLabelW + RightMargin);
  WordCountLabelY = (height - WordCountLabelH) / 2;

  WordLabelX = width - (WordCountLabelW + WordLabelW + RightMargin + InterWordSkip);
  WordLabelY = (height - WordLabelH) / 2;
  
  grad.setColorAt(0, QColor(137, 137, 145));
  grad.setColorAt(1, QColor(241, 244, 255));
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(grad));

  WordLabel->move(WordLabelX, WordLabelY);
  WordLabel->resize(WordLabelW, WordLabelH);
  
  WordCountLabel->move(WordCountLabelX, WordCountLabelY);
  WordCountLabel->resize(WordCountLabelW, WordCountLabelH);
  
  setPalette(pal);
}

/*****************************************************************************!
 * Function : SlotReferenceButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotReferenceButtonPushed(void)
{
  
}

/*****************************************************************************!
 * Function : SlotEditButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotEditButtonPushed(void)
{
  
}

/*****************************************************************************!
 * Function : SlotAnalyzeButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotAnalyzeButtonPushed(void)
{
  
}

/*****************************************************************************!
 * Function : SlotBlockViewButtonPushed
 *****************************************************************************/
void
TextControlBar::SlotBlockViewButtonPushed(void)
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
