/*****************************************************************************
 * FILE NAME    : MainWindow.h
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _mainwindow_h_
#define _mainwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainDisplayWindow.h"
#include "SystemConfig.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define MAIN_WINDOW_WIDTH                       640
#define MAIN_WINDOW_HEIGHT                      480
#define MAIN_WINDOW_Y                           100
#define MAIN_WINDOW_X                           100

/*****************************************************************************!
 * Exported Class : MainWindow
 *****************************************************************************/
class MainWindow : public QMainWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  MainWindow                    ();
  MainWindow                    (QWidget* );
  MainWindow                    (QString InBookName);
  
 //! Destructor
 public :
  ~MainWindow                   ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateActions           ();
  void                          CreateMenus             ();
  void                          CreateConnections       ();

 //! Private Data
 private :
  MainDisplayWindow*            displayWindow;
  QMenuBar*                     menubar;
  QMenu*                        fileMenu;
  QMenu*                        settingsMenu;
  QStatusBar*                   statusbar;
  QString                       BookName;
  
 //! Public Slots
 public slots :
  void                          SlotExit                (void);
  void                          SlotClearBookMarks      (void);

 //! Public Signals
 signals :
  void                          SignalClearBookMarks    (void);

 //! Public Actions
 public :
  QAction*                      ActionExit;
  QAction*                      ActionClearBookMarks;

};

#endif /* _mainwindow_h_*/
