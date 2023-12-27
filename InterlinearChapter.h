/*****************************************************************************
 * FILE NAME    : InterlinearChapter.h
 * DATE         : October 17 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/
#ifndef _interlinerarchapter_h_
#define _interlinerarchapter_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include"InterlinearVerse.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : InterlinearChapter
 *****************************************************************************/
class InterlinearChapter : public QWidget
{
 //! Constructors
 public :
  InterlinearChapter            (int InBookIndex, int InChapterNumber);

 //! Destructor
 public :
  ~InterlinearChapter           ();

 //! Public Methods
 public :
  void                          AddVerse                (InterlinearVerse* InVerse);
  int                           GetVerseCount           ();
  InterlinearVerse*             GetVerseByIndex         (int InIndex);
  int                           GetBookIndex            ();
  int                           GetChapterNumber        ();
  InterlinearWord*              FindWordByLocation      (QPoint InMouseCursor);
  void                          Read                    ();
  static int                    AddInterlinearChapterCB (void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  void                          ReadVerses              ();

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
  int                           bookIndex;
  int                           chapterNumber;
  QList<InterlinearVerse*>      verses;
};

#endif /* _interlinerarchapter_h_*/
