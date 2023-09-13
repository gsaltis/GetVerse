/*****************************************************************************
 * FILE NAME    : SystemConfig.h
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _systemconfig_h_
#define _systemconfig_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SystemConfig
 *****************************************************************************/
class SystemConfig : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SystemConfig                  ();

 //! Destructor
 public :
  ~SystemConfig                 ();

 //! Public Methods
 public :
  QSize                         GetMainWindowSize       (void);
  void                          SetMainWindowSize       (QSize InMainWindowSize);
  QPoint                        GetMainWindowLocation   (void);
  void                          SetMainWindowLocation   (QPoint InMainWindowPosition);
  void                          ReadJSON                (QString InFilename);

 //! Public Data
 public :
  static QString                SystemName;

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);

 //! Private Data
 private :
  QSize                         MainWindowSize;
  QPoint                        MainWindowLocation;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _systemconfig_h_*/
