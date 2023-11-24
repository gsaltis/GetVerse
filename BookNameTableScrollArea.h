/*****************************************************************************
 * FILE NAME    : BookNameTableScrollArea.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _booknametablescrollarea_h_
#define _booknametablescrollarea_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QScrollArea>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameTableInnerTable.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_NAME_TABLE_SCROLL_AREA_X      0
#define BOOK_NAME_TABLE_SCROLL_AREA_Y      0
#define BOOK_NAME_TABLE_SCROLL_AREA_WIDTH  200
#define BOOK_NAME_TABLE_SCROLL_AREA_HEIGHT 200

/*****************************************************************************!
 * Exported Class : BookNameTableScrollArea
 *****************************************************************************/
class BookNameTableScrollArea : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  BookNameTableScrollArea       ();

 //! Destructor
 public :
  ~BookNameTableScrollArea      ();

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
  BookNameTableInnerTable*      innerTable;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (int InBookIndex);
  void                          SlotMoveToBookChapter   (int InBook, int InChapter, int InVerse);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (int InBookIndex);
  void                          SignalMoveToBookChapter (int InBook, int InChapter, int InVerse);

 //! Public Actions
 public :

};

#endif /* _booknametablescrollarea_h_*/
