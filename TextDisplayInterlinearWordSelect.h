/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearWordSelect.h
 * DATE         : December 27 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearwordselect_h_
#define _textdisplayinterlinearwordselect_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceForm.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_X 200
#define TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_Y 200
#define TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_WIDTH 300
#define TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearWordSelect
 *****************************************************************************/
class TextDisplayInterlinearWordSelect : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayInterlinearWordSelect ();

 //! Destructor
 public :
  ~TextDisplayInterlinearWordSelect ();

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
  void                          GetWordReferences       (QString InStrongsWord);

 //! Private Data
 private :
  StrongsReferenceForm*         ReferenceWindow;

 //! Public Slots
 public slots :
  void                          SlotSelectStrongsWord   (QString InStrongsWord);
  void                          SlotCloseStrongsReference (void);

 //! Public Signals
 signals :
  void                          SignalVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SignalVerseReferencesStart (void);
  void                          SignalCloseStrongsReference (void);

 //! Public Actions
 public :

};

#endif /* _textdisplayinterlinearwordselect_h_*/
