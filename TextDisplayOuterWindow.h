/*****************************************************************************
 * FILE NAME    : TextDisplayOuterWindow.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayouterwindow_h_
#define _textdisplayouterwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SectionHeader.h"
#include "TextDisplayReferenceWindow.h"
#include "BookInfo.h"
#include "TextDisplayViewWindow.h"
#include "TextDisplayViewScrollWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_OUTER_WINDOW_X     200
#define TEXT_DISPLAY_OUTER_WINDOW_Y     200
#define TEXT_DISPLAY_OUTER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_OUTER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayOuterWindow
 *****************************************************************************/
class TextDisplayOuterWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayOuterWindow        ();

 //! Destructor
 public :
  ~TextDisplayOuterWindow       ();

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
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);

 //! Private Data
 private :
  SectionHeader*                header;
  TextDisplayReferenceWindow*   referenceWindow;
  TextDisplayViewScrollWindow*  viewWindow;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (int InBookIndex);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo*);

 //! Public Actions
 public :

};

#endif /* _textdisplayouterwindow_h_*/
