/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayWord.h
 * DATE         : December 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencedisplayword_h_
#define _strongsreferencedisplayword_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayWord.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_DISPLAY_WORD_X 200
#define STRONGS_REFERENCE_DISPLAY_WORD_Y 200
#define STRONGS_REFERENCE_DISPLAY_WORD_WIDTH 200
#define STRONGS_REFERENCE_DISPLAY_WORD_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceDisplayWord
 *****************************************************************************/
class StrongsReferenceDisplayWord : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceDisplayWord   ();

 //! Destructor
 public :
  ~StrongsReferenceDisplayWord  ();

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

 //! Private Data
 private :
  StrongsReferenceDisplayWord*  Display;

 //! Public Slots
 public slots :
  void                          SlotVerseReferenceClear (void);
  void                          SlotStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _strongsreferencedisplayword_h_*/
