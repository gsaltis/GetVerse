/*****************************************************************************
 * FILE NAME    : StrongsReferenceToolBar.cpp
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
#include "StrongsReferenceToolBar.h"

/*****************************************************************************!
 * Function : StrongsReferenceToolBar
 *****************************************************************************/
StrongsReferenceToolBar::StrongsReferenceToolBar
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~StrongsReferenceToolBar
 *****************************************************************************/
StrongsReferenceToolBar::~StrongsReferenceToolBar
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceToolBar::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  ActionClosePushed = new QAction("ClosePushed", this);
  connect(ActionClosePushed, SIGNAL(triggered()), this, SLOT(SlotClosePushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceToolBar::CreateSubWindows()
{
  //! Create the Close button
  Close = new QPushButton();
  Close->setParent(this);
  Close->move(1, 1);
  Close->setIcon(QIcon(QPixmap(":/Images/Close.png")));
  Close->resize(STRONGS_REFERENCE_TOOL_BAR_HEIGHT - 2, STRONGS_REFERENCE_TOOL_BAR_HEIGHT - 2);
  connect(Close, SIGNAL(pressed()), this, SLOT(SlotClosePushed()));

  //! Create label
  StrongsReferenceLabel = new QLabel();
  StrongsReferenceLabel->setParent(this);
  StrongsReferenceLabel->move(5, 1);
  StrongsReferenceLabel->resize(100, STRONGS_REFERENCE_TOOL_BAR_HEIGHT - 2);
  StrongsReferenceLabel->setText("-");
  StrongsReferenceLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  StrongsReferenceLabel->setFont(QFont("Arial", 10, QFont::Bold));
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceToolBar::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceToolBar::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceToolBar::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   closeX;
  int                                   closeY;
  int                                   closeH;
  int                                   closeW;
  QPalette                              pal;
  QSize					size;  
  int					height;
  int                                   width;
  
  size = InEvent->size();
  height = size.height();
  width = size.width();

  closeW = Close->size().width();
  closeH = Close->size().height();
  closeY = Close->pos().y();
  closeX = width - (closeW + 1);
  
  Close->move(closeX, closeY);
  Close->resize(closeW, closeH);
  
  QLinearGradient                       grad(0, 0, 0, height);
  grad.setColorAt(0, QColor(137, 137, 145));
  grad.setColorAt(1, QColor(241, 244, 255));
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(grad));
  setPalette(pal);
}

/*****************************************************************************!
 * Function : SlotClosePushed
 *****************************************************************************/
void
StrongsReferenceToolBar::SlotClosePushed(void)
{
  emit SignalClose();
}

/*****************************************************************************!
 * Function : GetStrongsReference
 *****************************************************************************/
QString
StrongsReferenceToolBar::GetStrongsReference(void)
{
  return StrongsReference;  
}

/*****************************************************************************!
 * Function : SetStrongsReference
 *****************************************************************************/
void
StrongsReferenceToolBar::SetStrongsReference
(QString InStrongsReference)
{
  StrongsReference = InStrongsReference;
  StrongsReferenceLabel->setText(StrongsReference);
}
