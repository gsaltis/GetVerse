/*****************************************************************************
 * FILE NAME    : BookMarkSet.h
 * DATE         : December 10 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookmarkset_h_
#define _bookmarkset_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookMark.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOKMARK_SET_MAX_COUNT  9

/*****************************************************************************!
 * Exported Class : BookMarkSet
 *****************************************************************************/
class BookMarkSet : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookMarkSet                   ();

 //! Destructor
 public :
  ~BookMarkSet                  ();

 //! Public Methods
 public :
  void                          Read                    (void);
  BookMark*                     FindByIndex             (int InIndex);
  void                          SetBookMark             (int InIndex, int InBook, int InChapter, int InVerse);
  void                          AddBookMark             (int InBook, int InChapter, int InVerse);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);
  int                           FindNextAvailableIndex  (void);

 //! Private Data
 private :
  QHash<int, BookMark*>         Bookmarks;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _bookmarkset_h_*/
