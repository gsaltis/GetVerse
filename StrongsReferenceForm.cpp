/*****************************************************************************
 * FILE NAME    : StrongsReferenceForm.cpp
 * DATE         : December 28 2023
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
#include "StrongsReferenceForm.h"

/*****************************************************************************!
 * Function : StrongsReferenceForm
 *****************************************************************************/
StrongsReferenceForm::StrongsReferenceForm
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
 * Function : ~StrongsReferenceForm
 *****************************************************************************/
StrongsReferenceForm::~StrongsReferenceForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceForm::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceForm::CreateSubWindows()
{
  toolbar = new StrongsReferenceToolBar();  
  toolbar->setParent(this);
  Splitter = new StrongsReferenceFormSplitter();
  Splitter->setParent(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceForm::CreateConnections()
{
  connect(toolbar,
          StrongsReferenceToolBar::SignalClose,
          this,
          StrongsReferenceForm::SlotCloseStrongsReference);
  connect(this,
          StrongsReferenceForm::SignalVerseReferenceClear,
          Splitter,
          StrongsReferenceFormSplitter::SlotVerseReferenceClear);
  connect(this,
          StrongsReferenceForm::SignalVerseReferenceSelected,
          Splitter,
          StrongsReferenceFormSplitter::SlotVerseReferenceSelected);
  connect(Splitter,
          StrongsReferenceFormSplitter::SignalStrongsReferenceSelected,
          this,
          StrongsReferenceForm::SlotStrongsReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceForm::InitializeSubWindows()
{
  toolbar = NULL;  
  Splitter = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceForm::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   SplitterW;
  int                                   SplitterH;
  int                                   SplitterY;
  int                                   SplitterX;
  
  int                                   toolbarW;
  int                                   toolbarH;
  int                                   toolbarY;
  int                                   toolbarX;

  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;

  toolbarX = 0;
  toolbarY = 0;
  toolbarW = width;
  toolbarH = STRONGS_REFERENCE_TOOL_BAR_HEIGHT;
  toolbar->move(toolbarX, toolbarY);
  toolbar->resize(toolbarW, toolbarH);

  SplitterX = 0;
  SplitterY = STRONGS_REFERENCE_TOOL_BAR_HEIGHT;
  SplitterW = width;
  SplitterH = height - STRONGS_REFERENCE_TOOL_BAR_HEIGHT;
  Splitter->move(SplitterX, SplitterY);
  Splitter->resize(SplitterW, SplitterH);

}

/*****************************************************************************!
 * Function : SlotCloseStrongsReference
 *****************************************************************************/
void
StrongsReferenceForm::SlotCloseStrongsReference(void)
{
  emit SignalCloseStrongsReference();  
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceForm::SlotVerseReferenceClear(void)
{
  emit SignalVerseReferenceClear();  
}

/*****************************************************************************!
 * Function : SlotVerseReferenceSelected
 *****************************************************************************/
void
StrongsReferenceForm::SlotVerseReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalVerseReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}

/*****************************************************************************!
 * Function : GetStrongsReference
 *****************************************************************************/
QString
StrongsReferenceForm::GetStrongsReference(void)
{
  return StrongsReference;  
}

/*****************************************************************************!
 * Function : SetStrongsReference
 *****************************************************************************/
void
StrongsReferenceForm::SetStrongsReference
(QString InStrongsReference)
{
  StrongsReference = InStrongsReference;
  toolbar->SetStrongsReference(StrongsReference);
}

/*****************************************************************************!
 * Function : SlotStrongsReferenceSelected
 *****************************************************************************/
void
StrongsReferenceForm::SlotStrongsReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  emit SignalStrongsReferenceSelected(InBookNumber, InChapterNumber, InVerseNumber);  
}
