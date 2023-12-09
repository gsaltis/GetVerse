/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.h
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _maindisplaywindow_h_
#define _maindisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameWindow.h"
#include "MainMessageWindow.h"
#include "TextDisplayOuterWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainDisplayWindow
 *****************************************************************************/
class MainDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainDisplayWindow             (QString InBookName);

 //! Destructor
 public :
  ~MainDisplayWindow            ();

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
  void                          InitializeSubWindows    ();
  void                          CreateSubWindows        ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);

 //! Private Data
 private :
  BookNameWindow*               bookNameWindow;
  MainMessageWindow*            messageWindow;
  TextDisplayOuterWindow*       displayWindow;
  QString                       BookName;

 //! Public Slots
 public slots :
  void                          SlotShowProgressBar     (void);
  void                          SlotHideProgressBar     (void);
  void                          SlotUpdateProgressBar   (int InValue);
  void                          SlotSetProgressBar      (int InMin, int InMax);
  void                          SlotSetStartupBookmark  (int InBook, int InChapter, int InVerse);
  void                          SlotSetStartupBookmarkInfo  (BookInfo* InBookInfo, int InChapter);

 //! Public Signals
 signals :
  void                          SignalHideProgressBar   (void);
  void                          SignalShowProgressBar   (void);
  void                          SignalSetProgressBar    (int InMin, int InMax);
  void                          SignalUpdateProgressBar (int InValue);
  void                          SignalMoveToBookChapter (int InBook, int InChapter, int InVerse);

 //! Public Actions
 public :

};

#endif /* _maindisplaywindow_h_*/
