/*****************************************************************************
 * FILE NAME    : BookNameWindow.h
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _booknamewindow_h_
#define _booknamewindow_h_

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
#include "BookNameTable.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_NAME_WINDOW_X              200
#define BOOK_NAME_WINDOW_Y              200
#define BOOK_NAME_WINDOW_WIDTH          300
#define BOOK_NAME_WINDOW_HEIGHT         200

/*****************************************************************************!
 * Exported Class : BookNameWindow
 *****************************************************************************/
class BookNameWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  BookNameWindow                ();

 //! Destructor
 public :
  ~BookNameWindow               ();

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
  void                          PopulateWindow          (void);
  void                          CreateConnections       (void);

 //! Private Data
 private :
  SectionHeader*                header;
  BookNameTable*                nameTable;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (int InBookIndex);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (int InBookIndex);

 //! Public Actions
 public :

};

#endif /* _booknamewindow_h_*/
