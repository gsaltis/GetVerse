/*****************************************************************************
 * FILE NAME    : BookNameTableInnerTable.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _booknametableinnertable_h_
#define _booknametableinnertable_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTableWidgetItem>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameTableItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_NAME_TABLE_INNER_TABLE_X           0
#define BOOK_NAME_TABLE_INNER_TABLE_Y           0
#define BOOK_NAME_TABLE_INNER_TABLE_WIDTH       200
#define BOOK_NAME_TABLE_INNER_TABLE_HEIGHT      200

/*****************************************************************************!
 * Exported Class : BookNameTableInnerTable
 *****************************************************************************/
class BookNameTableInnerTable : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookNameTableInnerTable       ();

 //! Destructor
 public :
  ~BookNameTableInnerTable      ();

 //! Public Methods
 public :
  int                           GetTableHeight          ();
  
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
  void                          Populate                (void);

 //! Private Data
 private :
  std::vector<BookNameTableItem*>       items;
  int                           topMargin;
  int                           tableHeight;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (int InBookIndex);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (int InBookIndex);

 //! Public Actions
 public :

};

#endif /* _booknametableinnertable_h_*/
