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
  (void)InFilename;
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
SystemConfig::Initialize(void)
{
  MainWindowLocation    = QPoint(560, 0);
  MainWindowSize        = QSize(1360, 1020);
}
