/*****************************************************************************
 * FILE NAME    : StrongsReferenceForm.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferenceform_h_
#define _strongsreferenceform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceToolBar.h"
#include "StrongsReferenceFormSplitter.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_FORM_X        200
#define STRONGS_REFERENCE_FORM_Y        200
#define STRONGS_REFERENCE_FORM_WIDTH    200
#define STRONGS_REFERENCE_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : StrongsReferenceForm
 *****************************************************************************/
class StrongsReferenceForm : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceForm          ();

 //! Destructor
 public :
  ~StrongsReferenceForm         ();

 //! Public Methods
 public :
  QString                       GetStrongsReference     (void);
  void                          SetStrongsReference     (QString InStrongsReference);

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
  StrongsReferenceToolBar*      toolbar;
  StrongsReferenceFormSplitter* Splitter;
  QString                       StrongsReference;

 //! Public Slots
 public slots :
  void                          SlotCloseStrongsReference (void);
  void                          SlotVerseReferenceClear (void);
  void                          SlotVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SlotStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Signals
 signals :
  void                          SignalCloseStrongsReference (void);
  void                          SignalVerseReferenceClear (void);
  void                          SignalVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SignalStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _strongsreferenceform_h_*/
