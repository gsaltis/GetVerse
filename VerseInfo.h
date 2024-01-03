/*****************************************************************************
 * FILE NAME    : VerseInfo.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _verseinfo_h_
#define _verseinfo_h_

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
 * Exported Class : VerseInfo
 *****************************************************************************/
class VerseInfo : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  VerseInfo                     ();
  VerseInfo                     (int InBook, int InChapter, int InVerse, QString InText);
  
 //! Destructor
 public :
  ~VerseInfo                    ();

 //! Public Methods
 public :
  int                           GetBook                 (void);
  void                          SetBook                 (int InBook);
  int                           GetChapter              (void);
  void                          SetChapter              (int InChapter);
  int                           GetVerse                (void);
  void                          SetVerse                (int InVerse);
  QString                       GetText                 (void);
  void                          SetText                 (QString InText);

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
  QString                       Text;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _verseinfo_h_*/
