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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayinterlinearwordselect_h_*/
