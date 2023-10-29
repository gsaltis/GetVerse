/*****************************************************************************
 * FILE NAME    : BookInfo.h
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookinfo_h_
#define _bookinfo_h_

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

/*****************************************************************************!
 * Exported Class : BookInfo
 *****************************************************************************/
class BookInfo : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookInfo                      ();

 //! Destructor
 public :
  ~BookInfo                     ();

 //! Public Methods
 public :
  QString                               GetCapitalizedBookName  ();
  
 //! Public Data
 public :
  QString                               name;
  QString                               nameAbbrev;
  int                                   chapters;
  int                                   index;
  int                                   bookOrder;
  int                                   bookGroup;
  int                                   hebrewBookOrder;
  int                                   hebrewBookGroup;
  int                                   groupEnd;
  
 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _bookinfo_h_*/
