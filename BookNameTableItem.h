/*****************************************************************************
 * FILE NAME    : BookNameTableItem.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _booknametableitem_h_
#define _booknametableitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_NAME_TABLE_ITEM_X          0
#define BOOK_NAME_TABLE_ITEM_Y          0
#define BOOK_NAME_TABLE_ITEM_WIDTH      200
#define BOOK_NAME_TABLE_ITEM_HEIGHT     22

/*****************************************************************************!
 * Exported Class : BookNameTableItem
 *****************************************************************************/
class BookNameTableItem : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookNameTableItem             (BookInfo* InBookInfo);

 //! Destructor
 public :
  ~BookNameTableItem            ();

 //! Public Methods
 public :
  QString                       GetName                 (void);
  void                          SetName                 (QString InName);
  int                           GetIndex                ();
  
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
  void                          paintEvent              (QPaintEvent* InEvent);
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          leaveEvent              (QEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Private Data
 private :
  BookInfo*                     bookInfo;
  QLabel*                       bookName;
  QLabel*                       bookNumberLabel;
  QString                       name;
  int                           bookNumber;
  QString                       textColorName;
  QString                       backgroundColorName;
  int                           index;
  QColor                        backgroundColor;
  QColor                        textColor;
  QColor                        selectedColor;
  QColor                        selectedTextColor;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalBookSelected      (int InBookIndex);

 //! Public Actions
 public :

};

#endif /* _booknametableitem_h_*/
