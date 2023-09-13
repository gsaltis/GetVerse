/*****************************************************************************
 * FILE NAME    : SectionHeader.cpp
 * DATE         : September 11 2023
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
#include "SectionHeader.h"

/*****************************************************************************!
 * Function : SectionHeader
 *****************************************************************************/
SectionHeader::SectionHeader
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(208, 208, 208)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SectionHeader
 *****************************************************************************/
SectionHeader::~SectionHeader
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SectionHeader::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  setFrameShadow(QFrame::Raised);
  setFrameStyle(QFrame::Panel);
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SectionHeader::CreateSubWindows()
{
  //! Create label
  text = new QLabel();
  text->setParent(this);
  text->move(5, 2);
  text->resize(100, 20);
  text->setText("Text");
  text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SectionHeader::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SectionHeader::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   textX;
  int                                   textY;
  int                                   textH;
  int                                   textW;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();
  textX = text->pos().x();
  textW = (width - textX);
  textY = text->pos().y();
  textH = height - (textY * 2);

  text->resize(textW, textH);
  text->move(textX, textY);
}

/*****************************************************************************!
 * Function : SetText
 *****************************************************************************/
void
SectionHeader::SetText
(QString InText)
{
  text->setText(InText);
}
