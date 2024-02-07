/*****************************************************************************
 * FILE NAME    : BookInfoManager.h
 * DATE         : December 17 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookinfomanager_h_
#define _bookinfomanager_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QComboBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define DUPLICATE_BOOK                          1
#define BOOK_NOT_FOUND                          2
#define BOOK_FOUND                              3

/*****************************************************************************!
 * Exported Class : BookInfoManager
 *****************************************************************************/
class BookInfoManager : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookInfoManager               ();

 //! Destructor
 public :
  ~BookInfoManager              ();

 //! Public Methods
 public :
  int                           VerifyBookName          (QString InBookName);
  void                          AddBookInfo             (BookInfo* InBook);
  BookInfo*                     FindBookByIndex         (int InIndex);
  BookInfo*                     GetSearchableBookName   (QString InBookName);
  int                           GetSize                 (void);
  BookInfo*                     GetByIndex              (int InIndex);
  BookInfo*                     GetBookByName           (QString InBookName, bool InUseAbbrev = false);
  int                           GetBookCount            (void);
  BookInfo*                     GetBookByIndex          (int InIndex);
  void                          PopulateBookNameCombo   (QComboBox* InComboBox);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  QList<BookInfo*>              Books;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _bookinfomanager_h_*/
