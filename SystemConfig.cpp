/*****************************************************************************
 * FILE NAME    : SystemConfig.cpp
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QJsonDocument>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SystemConfig.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
QString SystemConfig::SystemName = "GetVerse";

/*****************************************************************************!
 * Function : SystemConfig
 *****************************************************************************/
SystemConfig::SystemConfig
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~SystemConfig
 *****************************************************************************/
SystemConfig::~SystemConfig
()
{
}

/*****************************************************************************!
 * Function : GetMainWindowSize
 *****************************************************************************/
QSize
SystemConfig::GetMainWindowSize(void)
{
  return MainWindowSize;  
}

/*****************************************************************************!
 * Function : SetMainWindowSize
 *****************************************************************************/
void
SystemConfig::SetMainWindowSize
(QSize InMainWindowSize)
{
  MainWindowSize = InMainWindowSize;  
}

/*****************************************************************************!
 * Function : GetMainWindowLocation
 *****************************************************************************/
QPoint
SystemConfig::GetMainWindowLocation(void)
{
  return MainWindowLocation;  
}

/*****************************************************************************!
 * Function : SetMainWindowLocation
 *****************************************************************************/
void
SystemConfig::SetMainWindowLocation
(QPoint InMainWindowLocation)
{
  MainWindowLocation = InMainWindowLocation;  
}

/*****************************************************************************!
 * Function : ReadJSON
 *****************************************************************************/
void
SystemConfig::ReadJSON
(QString InFilename)
{
  int                                   blue;
  int                                   green;
  int                                   red;
  QJsonObject                           blockWindowObj;
  QJsonObject                           blockWindowBackgroundObj;
  QJsonObject                           mainWindowLocation;
  QJsonObject                           mainWindowSize;
  int                                   h;
  int                                   w;
  int                                   y;
  int                                   x;
  QFile                                 file(InFilename);
  QByteArray                            bytes;
  QJsonDocument                         doc;
  QJsonObject                           obj;
  QJsonObject                           mainWindowObj;
  QJsonObject                           wordItemObj;
  
  if ( ! file.open(QIODevice::ReadOnly) ) {
    return;
  }
  bytes = file.readAll();
  file.close();
  doc = QJsonDocument::fromJson(bytes);
  obj = doc.object();
  mainWindowObj = obj["MainWindow"].toObject();

  mainWindowLocation = mainWindowObj["Location"].toObject();
  x = mainWindowLocation["x"].toInt();
  y = mainWindowLocation["y"].toInt();

  mainWindowSize = mainWindowObj["Size"].toObject();
  w = mainWindowSize["width"].toInt();
  h = mainWindowSize["height"].toInt();

  MainWindowLocation = QPoint(x, y);
  MainWindowSize = QSize(w, h);

  blockWindowObj = obj["BlockWindow"].toObject();
  blockWindowBackgroundObj = blockWindowObj["Background"].toObject();
  red = blockWindowBackgroundObj["red"].toInt();
  green = blockWindowBackgroundObj["green"].toInt();
  blue = blockWindowBackgroundObj["blue"].toInt();
  BlockWindowBackgroundColor = QColor(red, green, blue);

  wordItemObj = obj["WordItem"].toObject();
  SetWordItemFontFamily(wordItemObj["Family"].toString());
  SetWordItemFontSize(wordItemObj["Size"].toInt());
  SetWordItemFontBold(wordItemObj["Bold"].toBool());
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
SystemConfig::Initialize(void)
{
  MainWindowLocation            = QPoint(0, 0);
  MainWindowSize                = QSize(1920, 1020);
  BlockWindowBackgroundColor    = QColor(255, 255, 255);
  WordItemFont                  = QFont();
}

/*****************************************************************************!
 * Function : GetBlockWindowBackgroundColor
 *****************************************************************************/
QColor
SystemConfig::GetBlockWindowBackgroundColor(void)
{
  return BlockWindowBackgroundColor;  
}

/*****************************************************************************!
 * Function : SetBlockWindowBackgroundColor
 *****************************************************************************/
void
SystemConfig::SetBlockWindowBackgroundColor
(QColor InBlockWindowBackgroundColor)
{
  BlockWindowBackgroundColor = InBlockWindowBackgroundColor;  
}

/*****************************************************************************!
 * Function : GetWordItemFont
 *****************************************************************************/
QFont
SystemConfig::GetWordItemFont
()
{
  return WordItemFont;
}

/*****************************************************************************!
 * Function : SetWordItemFont
 *****************************************************************************/
void
SystemConfig::SetWordItemFont
(QFont InFont)
{
  WordItemFont = QFont(InFont);
}

/*****************************************************************************!
 * Function : SetWordItemFontFamily
 *****************************************************************************/
void
SystemConfig::SetWordItemFontFamily
(QString InFontFamily)
{
  WordItemFont.setFamily(InFontFamily);
}

/*****************************************************************************!
 * Function : SetWordItemFontSize
 *****************************************************************************/
void
SystemConfig::SetWordItemFontSize
(int InFontSize)
{
  WordItemFont.setPointSize(InFontSize);
}

/*****************************************************************************!
 * Function : SetWordItemFontBold
 *****************************************************************************/
void
SystemConfig::SetWordItemFontBold
(bool InFontBold)
{
  WordItemFont.setWeight(InFontBold ? QFont::Bold : QFont::Normal);
}

