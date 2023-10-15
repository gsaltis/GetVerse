/*****************************************************************************
 * FILE NAME    : InterlinearContainer.h
 * DATE         : October 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _interlinearcontainer_h_
#define _interlinearcontainer_h_

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
#define INTERLINEAR_CONTAINER_X         200
#define INTERLINEAR_CONTAINER_Y         200
#define INTERLINEAR_CONTAINER_WIDTH     200
#define INTERLINEAR_CONTAINER_HEIGHT    200

/*****************************************************************************!
 * Exported Class : InterlinearContainer
 *****************************************************************************/
class InterlinearContainer : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  InterlinearContainer          ();

 //! Destructor
 public :
  ~InterlinearContainer         ();

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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _interlinearcontainer_h_*/
