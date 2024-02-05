/*****************************************************************************
 * FILE NAME    : WindowHeader.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WindowHeader.h"

/*****************************************************************************!
 * Function : WindowHeader
 *****************************************************************************/
WindowHeader::WindowHeader
(QString InText, QWidget* InParent) : QFrame(InParent)
{
  QPalette pal;

  text = InText;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 0, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~WindowHeader
 *****************************************************************************/
WindowHeader::~WindowHeader
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
WindowHeader::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
WindowHeader::CreateSubWindows()
{

  //! Create label  
  TextLabel = new QLabel();
  TextLabel->setParent(this);
  TextLabel->move(0, 10);
  TextLabel->resize(175, 35);
  TextLabel->setText(text);
  TextLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  TextLabel->setIndent(5);
  TextLabel->setFont(QFont("Segoe UI", 20, QFont::Bold));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
WindowHeader::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
WindowHeader::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 size;
  int                                   width;
  int                                   height;
  
  int                                   TextLabelW;
  int                                   TextLabelH;
  int                                   TextLabelY;
  int                                   TextLabelX;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  TextLabelX = 0;  
  TextLabelY = 0;
  TextLabelW = width;
  TextLabelH = height;
  
  TextLabel->move(TextLabelX, TextLabelY);
  TextLabel->resize(TextLabelW, TextLabelH);
}

/*****************************************************************************!
 * Function : SetBackgroundColor
 *****************************************************************************/
void
WindowHeader::SetBackgroundColor
(QColor InColor)
{
  QPalette pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(InColor));
  setPalette(pal);
  
}

/*****************************************************************************!
 * Function : DisplayFrame
 *****************************************************************************/
void
WindowHeader::DisplayFrame
(bool InDisplay)
{
  if ( InDisplay ) {
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Sunken);
    setLineWidth(1);
    return;
  }
  setFrameShadow(QFrame::Plain);
  setFrameShape(QFrame::NoFrame);
  setLineWidth(0);
}

/*****************************************************************************!
 * Function : SetFontSize
 *****************************************************************************/
void
WindowHeader::SetFontSize
(int InFontSize)
{
  TextLabel->setFont(QFont("Segoe UI", InFontSize, QFont::Bold));
}
