/*****************************************************************************
 * FILE NAME    : SystemSettings.h
 * DATE         : January 13 2024
 * PROJECT      : Get Verse
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _systemsettings_h_
#define _systemsettings_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QSettings>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SystemSettings
 *****************************************************************************/
class SystemSettings : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SystemSettings                ();

 //! Destructor
 public :
  ~SystemSettings               ();

 //! Public Methods
 public :
  int                           GetMainWindowX          ();
  void                          SetMainWindowX          (int InX);
  int                           GetMainWindowY          ();
  void                          SetMainWindowY          (int InY);
  int                           GetMainWindowWidth      ();
  void                          SetMainWindowWidth      (int InWidth);
  int                           GetMainWindowHeight     ();
  void                          SetMainWindowHeight     (int InHeight);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          VerifyMainWindowX       ();
  void                          VerifyMainWindowY       ();
  void                          VerifyMainWindowWidth   ();
  void                          VerifyMainWindowHeight  ();

 //! Private Data
 private :
  QSettings*                    Settings;
  QString                       OrgName;
  QString                       AppName;
  QString                       MainWindowXTag;
  int                           MainWindowXDefault;
  QString                       MainWindowYTag;
  int                           MainWindowYDefault;
  QString                       MainWindowWidthTag;
  int                           MainWindowWidthDefault;
  QString                       MainWindowHeightTag;
  int                           MainWindowHeightDefault;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _systemsettings_h_*/
