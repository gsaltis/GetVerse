/*****************************************************************************
 * FILE NAME    : StrongsReferenceFormSplitter.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferenceformsplitter_h_
#define _strongsreferenceformsplitter_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QSplitter>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceDisplayWindow.h"
#include "StrongsReferenceVerseWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_FORM_SPLITTER_X 200
#define STRONGS_REFERENCE_FORM_SPLITTER_Y 200
#define STRONGS_REFERENCE_FORM_SPLITTER_WIDTH 200
#define STRONGS_REFERENCE_FORM_SPLITTER_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceFormSplitter
 *****************************************************************************/
class StrongsReferenceFormSplitter : public QSplitter
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceFormSplitter  ();

 //! Destructor
 public :
  ~StrongsReferenceFormSplitter ();

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
  StrongsReferenceDisplayWindow* DisplayWindow;
  StrongsReferenceVerseWindow*  VerseWindow;

 //! Public Slots
 public slots :
  void                          SlotVerseReferenceClear (void);
  void                          SlotVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SlotStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Signals
 signals :
  void                          SignalVerseReferenceClear (void);
  void                          SignalVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SignalStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _strongsreferenceformsplitter_h_*/
