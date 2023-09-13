/*****************************************************************************
 * FILE NAME    : BookInfoTable.h
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookinfotable_h_
#define _bookinfotable_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTable>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_INFO_TABLE_X               200
#define BOOK_INFO_TABLE_Y               200
#define BOOK_INFO_TABLE_WIDTH           200
#define BOOK_INFO_TABLE_HEIGHT          200

/*****************************************************************************!
 * Exported Class : BookInfoTable
 *****************************************************************************/
class BookInfoTable : public QTable
{
  Q_OBJECT;

 //! Constructors
 public :
  BookInfoTable                 ();

 //! Destructor
 public :
  ~BookInfoTable                ();

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

#endif /* _bookinfotable_h_*/
