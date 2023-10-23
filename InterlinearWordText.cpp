/*****************************************************************************
 * FILE NAME    : InterlinearWordText.cpp
 * DATE         : October 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWordText.h"

/*****************************************************************************!
 * Function : InterlinearWordText
 *****************************************************************************/
InterlinearWordText::InterlinearWordText
()
{
}

/*****************************************************************************!
 * Function : ~InterlinearWordText
 *****************************************************************************/
InterlinearWordText::~InterlinearWordText
()
{
}

/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
InterlinearWordText::GetText
()
{
  return text;
}

/*****************************************************************************!
 * Function : GetFont
 *****************************************************************************/
QFont
InterlinearWordText::GetFont
()
{
  return font;
}

/*****************************************************************************!
 * Function : GetTextColor
 *****************************************************************************/
QColor
InterlinearWordText::GetTextColor
()
{
  return textColor;
}

/*****************************************************************************!
 * Function : GetBackgroundColor
 *****************************************************************************/
QColor
InterlinearWordText::GetBackgroundColor
()
{
  return backgroundColor;
}

/*****************************************************************************!
 * Function : SetText
 *****************************************************************************/
void
InterlinearWordText::SetText
(QString InText)
{
  text = InText;
}

/*****************************************************************************!
 * Function : SetFont
 *****************************************************************************/
void
InterlinearWordText::SetFont
(QFont InFont)
{
  font = InFont;
}

/*****************************************************************************!
 * Function : SetTextColor
 *****************************************************************************/
void
InterlinearWordText::SetTextColor
(QColor InTextColor)
{
  textColor = InTextColor;
}

/*****************************************************************************!
 * Function : SetBackgroundColor
 *****************************************************************************/
void
InterlinearWordText::SetBackgroundColor
(QColor InBackgroundColor)
{
  backgroundColor = InBackgroundColor;
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
InterlinearWordText::GetSize
(QFont InFont)
{
  QRect                                 rect;
  QFontMetrics							fm(InFont);

  rect = fm.boundingRect(text);
  return QSize(rect.width(), rect.height());
}

