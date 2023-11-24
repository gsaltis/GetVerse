/*****************************************************************************
 * FILE NAME    : ChapterHeaderWindow.cpp
 * DATE         : November 14 2023
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
#include "ChapterHeaderWindow.h"

/*****************************************************************************!
 * Function : ChapterHeaderWindow
 *****************************************************************************/
ChapterHeaderWindow::ChapterHeaderWindow
(QString InText, QWidget* InParent) : QWidget(InParent)
{
  text                  = InText;
  fontName              = "Arial";
  fontBold              = true;
  fontColorName         = "#880000";
  backgroundColorName   = "#E0E0E0";
  initialize();
}

/*****************************************************************************!
 * Function : ~ChapterHeaderWindow
 *****************************************************************************/
ChapterHeaderWindow::~ChapterHeaderWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
ChapterHeaderWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
ChapterHeaderWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
ChapterHeaderWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
ChapterHeaderWindow::paintEvent
(QPaintEvent*)
{
  int                                   pixelSize;
  QFont                                 font;
  QPainter                              painter(this);
  QBrush                                brush;
  QColor                                backgroundColor;
  QColor                                fontColor;
  QPen                                  pen;
  int                                   height;
  QRect                                 rect;
  QBrush                                backgroundBrush;
  QPen                                  backgroundPen;
  int                                   textY;
  int                                   textX;
  
  height = size().height();
  textY = height - 3;
  textX = 5;
  
  pixelSize = height;
  font.setFamily(fontName);
  font.setWeight(fontBold ? QFont::Bold : QFont::Normal);
  font.setPixelSize(pixelSize);

  //!
  backgroundColor = QColor::fromString(backgroundColorName);
  fontColor = QColor::fromString(fontColorName);

  rect = QRect(QPoint(0, 0), size());
  backgroundBrush = QBrush(backgroundColor);
  backgroundPen = QPen(backgroundColor);

  painter.setPen(backgroundPen);
  painter.setBrush(backgroundBrush);
  painter.drawRect(rect);

  //!
  pen = QPen(fontColor, 1);
  brush = QBrush(fontColor);
  painter.setFont(font);
  painter.setBrush(brush);
  painter.setPen(pen);

  painter.drawText(textX, textY, text);
}

/*****************************************************************************!
 * Function : SetText
 *****************************************************************************/
void
ChapterHeaderWindow::SetText
(QString InText)
{
  text = InText;
  repaint();
}

/*****************************************************************************!
 * Function : SlotTextChanged
 *****************************************************************************/
void
ChapterHeaderWindow::SlotTextChanged
(QString InText)
{
  SetText(InText);
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
ChapterHeaderWindow::SlotChapterChanged
(int InChapter)
{
  QString                               s;

  s = QString("Chapter %1").arg(InChapter);
  SetText(s);
}
