/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWordsWindow.h
 * DATE         : December 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencedisplaywordswindow_h_
#define _strongsreferencedisplaywordswindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayWord.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_DISPLAY_WORDS_WINDOW_X 200
#define STRONGS_REFERENCE_DISPLAY_WORDS_WINDOW_Y 200
#define STRONGS_REFERENCE_DISPLAY_WORDS_WINDOW_WIDTH 200
#define STRONGS_REFERENCE_DISPLAY_WORDS_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceDisplayWordsWindow
 *****************************************************************************/
class StrongsReferenceDisplayWordsWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceDisplayWordsWindow ();

 //! Destructor
 public :
  ~StrongsReferenceDisplayWordsWindow ();

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
  StrongsReferenceDisplayWord*  Display;

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

#endif /* _strongsreferencedisplaywordswindow_h_*/
