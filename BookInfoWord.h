/*****************************************************************************
 * FILE NAME    : BookInfoWord.h
 * DATE         : November 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _bookinfoword_h_
#define _bookinfoword_h_

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
 * Exported Class : BookInfoWord
 *****************************************************************************/
class BookInfoWord : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  BookInfoWord                  (int InBook, int InChapter, int InVerse, int InWordIndex, QString InWordText);

 //! Destructor
 public :
  ~BookInfoWord                 ();

 //! Public Methods
 public :
  int                           GetBook                 (void);
  int                           GetChapter              (void);
  int                           GetVerse                (void);
  int                           GetIndex                (void);
  QString                       GetWord                 ();
  bool                          IsEqual                 (int InBook, int InChapter, int InVerse, int InIndex);

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
  int                                   book;
  int                                   chapter;
  int                                   verse;
  int                                   index;
  QString                               word;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _bookinfoword_h_*/
