/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayScrollWindow.h
 * DATE         : December 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencedisplayscrollwindow_h_
#define _strongsreferencedisplayscrollwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QScrollArea>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayWordsWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_DISPLAY_SCROLL_WINDOW_X 200
#define STRONGS_REFERENCE_DISPLAY_SCROLL_WINDOW_Y 200
#define STRONGS_REFERENCE_DISPLAY_SCROLL_WINDOW_WIDTH 200
#define STRONGS_REFERENCE_DISPLAY_SCROLL_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceDisplayScrollWindow
 *****************************************************************************/
class StrongsReferenceDisplayScrollWindow : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceDisplayScrollWindow ();

 //! Destructor
 public :
  ~StrongsReferenceDisplayScrollWindow ();

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
  StrongsReferenceDisplayWordsWindow* WordsWindow;

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

#endif /* _strongsreferencedisplayscrollwindow_h_*/
