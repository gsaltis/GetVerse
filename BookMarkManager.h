/*****************************************************************************
 * FILE NAME    : BookMarkManager.h
 * DATE         : December 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookmarkmanager_h_
#define _bookmarkmanager_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QSettings>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookMark.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOK_MARK_MANAGER_MAX_COUNT             10

/*****************************************************************************!
 * Exported Class : BookMarkManager
 *****************************************************************************/
class BookMarkManager : public QWidget
{
  Q_OBJECT;

  //! Constructors
public :
  BookMarkManager               (QString InOrgName, QString InAppName);

  //! Destructor
public :
  ~BookMarkManager              ();

  //! Public Methods
public :
  void                          AddBookMark             (BookMark* InBookMark);
  BookMark*                     GetBookMark             (int InIndex);
  void                          Read                    ();
  void                          SetBookMark             (int InBook, int InChapter, int InVerse, int InWord);
  BookMark*                     FindBookMark            (int InBook, int InChapter, int InVerse);
  void                          Clear                   (void);
  BookMark*                     GetBookMarkByIndex      (int InIndex);
  
  //! Public Data
public :

  //! Protected Methods
protected :

  //! Protected Data
protected :

  //! Private Methods
private :
  void                          ShiftBookMarks          (void);

  //! Private Data
private :
  BookMark*                     bookMarks[BOOK_MARK_MANAGER_MAX_COUNT + 1];
  QSettings*                    settings;

  //! Public Slots
public slots :
  void                          SlotSetBookmark         (int InBook, int InChapter, int InVerse, int InWordIndex);

  //! Public Signals
signals :
  void                          SignalBookMarksUpdated  (void);

  //! Public Actions
public :

};

#endif /* _bookmarkmanager_h_*/
