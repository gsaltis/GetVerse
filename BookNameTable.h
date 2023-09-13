/*****************************************************************************
 * FILE NAME    : BookNameTable.h
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _booknametable_h_
#define _booknametable_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTableWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameTableScrollArea.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_NAME_TABLE_X               200
#define BOOK_NAME_TABLE_Y               200
#define BOOK_NAME_TABLE_WIDTH           200
#define BOOK_NAME_TABLE_HEIGHT          200

/*****************************************************************************!
 * Exported Class : BookNameTable
 *****************************************************************************/
class BookNameTable : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookNameTable                 ();

 //! Destructor
 public :
  ~BookNameTable                ();

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
  BookNameTableScrollArea*      scrollArea;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (int InBookIndex);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (int InBookIndex);

 //! Public Actions
 public :

};

#endif /* _booknametable_h_*/
