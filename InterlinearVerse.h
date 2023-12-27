/*****************************************************************************
 * FILE NAME    : InterlinearVerse.h
 * DATE         : October 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _interlinearverse_h_
#define _interlinearverse_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWord.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : InterlinearVerse
 *****************************************************************************/
class InterlinearVerse
{
 //! Constructors
 public :
  InterlinearVerse              (int InBookIndex, int InChapterNumber, int InVerseNumber, int InVerseID);

 //! Destructor
 public :
  ~InterlinearVerse             ();

 //! Public Methods
 public :
  void                          AddWord         	(InterlinearWord* InWord);
  int                           GetWordCount    	();
  InterlinearWord*              GetWordByIndex  	(int InIndex);
  InterlinearWord*              GetWordByID     	(int InID);
  int                           GetVerseID      	();
  int                           GetVerseNumber  	();
  int                           GetChapterNumber	();
  int                           GetBookIndex    	();
  void                          Read                    (void);
  InterlinearWord*              FindWordByLocation      (QPoint InMouseCursor);  
  static int                    AddInterlinearVerseCB   (void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  
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
  QList<InterlinearWord*>       words;
  int                           bookIndex;
  int                           chapterNumber;
  int                           verseNumber;
  int                           verseID;

};

#endif /* _interlinearverse_h_*/
