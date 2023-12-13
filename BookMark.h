/*****************************************************************************
 * FILE NAME    : BookMark.h
 * DATE         : December 09 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookmark_h_
#define _bookmark_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define BOOKMARK_MAX_COUNT                              9

/*****************************************************************************!
 * Exported Class : BookMark
 *****************************************************************************/
class BookMark : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookMark                      (int InIndex);
  BookMark                      (int InIndex, int InBook, int InChapter, int InVerse);

 //! Destructor
 public :
  ~BookMark                     ();

 //! Public Methods
 public :
  int                           GetBook                 (void);
  void                          SetBook                 (int InBook);
  int                           GetChapter              (void);
  void                          SetChapter              (int InChapter);
  int                           GetVerse                (void);
  void                          SetVerse                (int InVerse);
  int                           GetIndex                (void);
  void                          SetIndex                (int InIndex);
  void                          Read                    (QSettings* InSettings);
  void                          SetButton               (class BookmarkButton* InButton);
  void                          Set                     (int InBook, int InChapter, int InVerse);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);

 //! Private Data
 private :
  int                           Book;
  int                           Chapter;
  int                           Verse;
  int                           Index;
  class BookmarkButton*         button;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _bookmark_h_*/
