/*****************************************************************************
 * FILE NAME    : InterlinearWordDisplay.h
 * DATE         : December 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _interlinearworddisplay_h_
#define _interlinearworddisplay_h_

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
#define INTERLINEAR_WORD_DISPLAY_X      200
#define INTERLINEAR_WORD_DISPLAY_Y      200
#define INTERLINEAR_WORD_DISPLAY_WIDTH  200
#define INTERLINEAR_WORD_DISPLAY_HEIGHT 200

/*****************************************************************************!
 * Exported Class : InterlinearWordDisplay
 *****************************************************************************/
class InterlinearWordDisplay : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  InterlinearWordDisplay        ();

 //! Destructor
 public :
  ~InterlinearWordDisplay       ();

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

#endif /* _interlinearworddisplay_h_*/
