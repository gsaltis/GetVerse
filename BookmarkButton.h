/*****************************************************************************
 * FILE NAME    : BookmarkButton.h
 * DATE         : December 09 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookmarkbutton_h_
#define _bookmarkbutton_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"
#include "BookMark.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOKMARK_BUTTON_Y               1
#define BOOKMARK_BUTTON_WIDTH           80
#define BOOKMARK_BUTTON_HEIGHT          20

/*****************************************************************************!
 * Exported Class : BookmarkButton
 *****************************************************************************/
class BookmarkButton : public QPushButton
{
  Q_OBJECT;

  //! Constructors
public :
  BookmarkButton                (QWidget* InParent);
  BookmarkButton                (QWidget* InParent, BookInfo* InBook, int InChapter, int InVerse);
  BookmarkButton                (QWidget* InParent, BookMark* InBookMark);
  
  //! Destructor
public :
  ~BookmarkButton               ();

  //! Public Methods
public :
  void                          Set                     (BookInfo* InBook, int InChapter, int InVerse);

  //! Public Data
public :

  //! Protected Methods
protected :

  //! Protected Data
protected :

  //! Private Methods
private :
  void                          initialize              ();
  void                          CreateConnections       (void);

  //! Private Data
private :
  BookInfo*                     Book;
  int                           Chapter;
  int                           Verse;
  BookMark*                     bookMark;
  
  //! Public Slots
public slots :
  void                          SlotPushed              (void);

  //! Public Signals
signals :
  void                          SignalBookmarkSelected  (BookInfo* InBookInfo, int InChapter, int InVerse);

  //! Public Actions
public :

};

#endif /* _bookmarkbutton_h_*/
