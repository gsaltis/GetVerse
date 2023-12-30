/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWindow.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencedisplaywindow_h_
#define _strongsreferencedisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayScrollWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_DISPLAY_WINDOW_X 200
#define STRONGS_REFERENCE_DISPLAY_WINDOW_Y 200
#define STRONGS_REFERENCE_DISPLAY_WINDOW_WIDTH 200
#define STRONGS_REFERENCE_DISPLAY_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceDisplayWindow
 *****************************************************************************/
class StrongsReferenceDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceDisplayWindow ();

 //! Destructor
 public :
  ~StrongsReferenceDisplayWindow ();

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
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          CreateConnections       ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  StrongsReferenceDisplayScrollWindow* ScrollArea;

 //! Public Slots
 public slots :
  void                          SlotVerseReferenceClear (void);
  void                          SlotStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Signals
 signals :
  void                          SignalVerseReferenceClear (void);
  void                          SignalStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _strongsreferencedisplaywindow_h_*/
