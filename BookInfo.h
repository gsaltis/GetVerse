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
#include "BookInfoWord.h"
#include "VerseInfoSet.h"

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
  int                                   GetVerseCount           ();
  void                                  ReadVerses              ();
  void                                  AddLineText             (int InChapter, int InVerse, QString InVerseText);
  BookInfoWord*                         GetWord                 (int InChapter, int InVerse, int InIndex);
  int                                   GetWordCount            ();
  static int                            ReadVersesCB            (void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  int                                   GetChapterWordCount     (int InChapter);
  void                                  GetChapterWordIndices   (int InChapter, int &InStartIndex, int &InEndIndex);
  BookInfoWord*                         GetWordByIndex          (int InIndex);
  int                                   GetIndex                (void);
  int                                   GetChapterCount         (void);
  int                                   GetRightToLeft          (void);
  void                                  SetRightToLeft          (int InRightToLeft);
  QString                               GetName                 (void);
  static QString                        GetVerseText            (int InBookNumber, int InChapterNumber, int InVerseNumber);
  VerseInfoSet*                         GetVerses               ();

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
  QList<BookInfoWord*>                  wordItems;
  int                                   RightToLeft;
 
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
