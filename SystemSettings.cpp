/*****************************************************************************
 * FILE NAME    : SystemSettings.cpp
 * DATE         : January 13 2024
 * PROJECT      : Get Verse
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
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
#include "SystemSettings.h"

/*****************************************************************************!
 * Function : SystemSettings
 *****************************************************************************/
SystemSettings::SystemSettings
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~SystemSettings
 *****************************************************************************/
SystemSettings::~SystemSettings
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
SystemSettings::Initialize()
{
  OrgName = "White Barn";  
  AppName = "GetVerse";
  Settings = new QSettings(OrgName, AppName);
  MainWindowXTag = "MainWindow/X";
  MainWindowXDefault = 10;
  MainWindowYTag = "MainWindow/Y";
  MainWindowYDefault = 10;
  MainWindowWidthTag = "MainWindow/Width";
  MainWindowWidthDefault = 1000;
  MainWindowHeightTag = "MainWindow/Height";
  MainWindowHeightDefault = 800;
}

/*****************************************************************************!
 * Function : GetMainWindowX
 *****************************************************************************/
int
SystemSettings::GetMainWindowX
()
{
  VerifyMainWindowX();
  return Settings->value(MainWindowXTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyMainWindowX
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowX()
{
  if ( ! Settings->contains(MainWindowXTag) ) {  
    Settings->setValue(MainWindowXTag, MainWindowXDefault);
  }
}

/*****************************************************************************!
 * Function : SetMainWindowX
 *****************************************************************************/
void
SystemSettings::SetMainWindowX
(int InX)
{
  Settings->setValue(MainWindowXTag, InX);  
}

/*****************************************************************************!
 * Function : GetMainWindowY
 *****************************************************************************/
int
SystemSettings::GetMainWindowY
()
{
  VerifyMainWindowY();
  return Settings->value(MainWindowYTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyMainWindowY
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowY()
{
  if ( ! Settings->contains(MainWindowYTag) ) {  
    Settings->setValue(MainWindowYTag, MainWindowYDefault);
  }
}

/*****************************************************************************!
 * Function : SetMainWindowY
 *****************************************************************************/
void
SystemSettings::SetMainWindowY
(int InY)
{
  Settings->setValue(MainWindowYTag, InY);
}

/*****************************************************************************!
 * Function : GetMainWindowWidth
 *****************************************************************************/
int
SystemSettings::GetMainWindowWidth
()
{
  VerifyMainWindowWidth();
  return Settings->value(MainWindowWidthTag).toInt();
}
  
/*****************************************************************************!
 * Function : VerifyMainWindowWidth
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowWidth()
{
  if ( ! Settings->contains(MainWindowWidthTag) ) {  
    Settings->setValue(MainWindowWidthTag, MainWindowWidthDefault);
  }
}

/*****************************************************************************!
 * Function : SetMainWindowWidth
 *****************************************************************************/
void
SystemSettings::SetMainWindowWidth
(int InWidth)
{
  Settings->setValue(MainWindowWidthTag, InWidth);
}

/*****************************************************************************!
 * Function : GetMainWindowHeight
 *****************************************************************************/
int
SystemSettings::GetMainWindowHeight
()
{
  VerifyMainWindowHeight();
  return Settings->value(MainWindowHeightTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyMainWindowHeight
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowHeight()
{
  if ( ! Settings->contains(MainWindowHeightTag) ) {  
    Settings->setValue(MainWindowHeightTag, MainWindowHeightDefault);
  }
}

/*****************************************************************************!
 * Function : SetMainWindowHeight
 *****************************************************************************/
void
SystemSettings::SetMainWindowHeight
(int InHeight)
{
  Settings->setValue(MainWindowHeightTag, InHeight);
}
